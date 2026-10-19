"""Resolve watermark content once, independently of any template or GUI.

Visibility affects drawn content only; it never edits the photo's EXIF. Custom
places, signatures and filter names are separate fields, without implicit
substitution between them. Both layout adapters consume this same snapshot.
"""
from dataclasses import dataclass
from datetime import datetime


def parse_stamp(text):
    value = str(text or '').strip()
    for pattern in ('%Y-%m-%d %H:%M:%S', '%Y.%m.%d %H:%M:%S', '%Y:%m:%d %H:%M:%S'):
        try:
            return datetime.strptime(value[:19], pattern)
        except ValueError:
            pass
    return None


def split_stamp(text, want_date=True, want_time=True):
    """Select actual EXIF date/time independently, never inventing a timestamp."""
    if not text or not (want_date or want_time):
        return ''
    stamp = parse_stamp(text)
    if stamp is None:
        return str(text).strip() if want_date and want_time else ''
    return ' '.join(part for part in (
        stamp.strftime('%Y.%m.%d') if want_date else '',
        stamp.strftime('%H:%M:%S') if want_time else '') if part)


@dataclass(frozen=True)
class WatermarkInformation:
    camera: str
    settings: str
    stamp: str
    coordinates: str
    location_label: str
    signature: str
    signature_image: str
    filter_name: str
    title: str
    date_enabled: bool
    time_enabled: bool
    parameters_enabled: bool
    captured_at: datetime | None
    focal: str
    aperture: str
    speed: str
    iso: str

    @classmethod
    def from_options(cls, info, options, filter_name=None):
        fallback = str(getattr(options, 'fallback', '') or '').strip()
        override = bool(getattr(options, 'override', False)) and bool(fallback)
        brand = bool(getattr(options, 'brand', True))
        camera = fallback if override else (info.camera if brand else info.model.strip() or info.camera)
        camera = camera or fallback or '未知机型'
        if not getattr(options, 'device', True):
            camera = ''
        date = bool(getattr(options, 'date', True))
        time = bool(getattr(options, 'time', True))
        parameters = bool(getattr(options, 'details', True))
        exposure = info.exposure
        speed = (f'1/{round(1/exposure)}' if 0 < exposure < 1 else f'{exposure:g}') if exposure else ''
        name = getattr(options, 'filter_name', '') if filter_name is None else filter_name
        return cls(
            camera=camera, settings=info.settings if parameters else '',
            stamp=split_stamp(info.date, date, time),
            coordinates=info.coordinates if getattr(options, 'location', True) else '',
            location_label=str(getattr(options, 'location_label', '') or '').strip(),
            signature=str(getattr(options, 'signature', '') or '').strip(),
            signature_image=(str(getattr(options, 'signature_image', '') or '').strip()
                             if getattr(options, 'signature_image_enabled', True) else ''),
            filter_name=str(name or '') if getattr(options, 'caption', False) else '',
            title=str(getattr(options, 'title', '') or '').strip(),
            date_enabled=date, time_enabled=time, parameters_enabled=parameters,
            captured_at=parse_stamp(info.date),
            focal=f'{info.focal:g}' if parameters and info.focal else '',
            aperture=f'{info.aperture:g}' if parameters and info.aperture else '',
            speed=speed if parameters else '', iso=str(info.iso or '') if parameters else '')

    @property
    def summary_fields(self):
        """Supplementary information keeps the currently approved three fields."""
        return [(name, value) for name, value in (
            ('time', self.stamp), ('camera', self.camera), ('coordinates', self.coordinates)) if value]

    def template_fields(self, expression, ident, rendered_text):
        """Identify information actually drawn in a native template text node.

        This is called after visibility and layout, so hidden nodes do not count.
        Date and clock are tracked separately; a date does not cover a clock.
        A template clock to the minute already covers time, without appending a
        second copy solely to show seconds.
        """
        if not rendered_text.strip():
            return frozenset()
        if expression.startswith('@model='):
            return frozenset({'camera'}) if self.camera and 'version' not in ident.lower() else frozenset()
        if expression.startswith('@location='):
            value = self.template_text(expression, ident)
            return frozenset({'coordinates'}) if self.coordinates and value == self.coordinates else frozenset()
        if not expression.startswith('@time='):
            return frozenset()
        fields = set()
        if self.captured_at is None:
            if rendered_text == self.stamp:
                if self.date_enabled:fields.add('date')
                if self.time_enabled:fields.add('clock')
        else:
            if self.date_enabled and self.captured_at.strftime('%Y.%m.%d') in rendered_text:
                fields.add('date')
            if self.time_enabled and self.captured_at.strftime('%H:%M') in rendered_text:
                fields.add('clock')
        return frozenset(fields)

    def missing_summary_fields(self, covered):
        """Supplement missing components only, without repeating native fields."""
        stamp = split_stamp(self.stamp,
                            self.date_enabled and 'date' not in covered,
                            self.time_enabled and 'clock' not in covered)
        # self.stamp can contain only a date or only a clock. Use the original
        # parsed EXIF value to preserve independent selection in those cases.
        if self.captured_at is not None:
            stamp = split_stamp(self.captured_at.strftime('%Y-%m-%d %H:%M:%S'),
                                self.date_enabled and 'date' not in covered,
                                self.time_enabled and 'clock' not in covered)
        return [(name, value) for name, value in (
            ('time', stamp),
            ('camera', self.camera if 'camera' not in covered else ''),
            ('coordinates', self.coordinates if 'coordinates' not in covered else '')) if value]

    @property
    def desktop_caption(self):
        return '  ·  '.join(value for value in (self.signature, self.filter_name) if value)

    @property
    def desktop_location(self):
        return '  ·  '.join(value for value in (self.location_label, self.coordinates) if value)

    def allows_optional(self, setting):
        visible = {
            'type_model': bool(self.camera),
            'type_exif': bool(self.settings),
            'type_time': bool(self.stamp),
            'type_location': bool(self.coordinates or self.location_label),
            'type_custom_text': bool(self.signature),
        }
        return visible.get(setting, True)

    def template_text(self, text, ident=''):
        if ident == 'live_moment' and self.title:
            return self.title
        if text in ('F', 'ISO', 'S', 'mm'):
            value = {'F': self.aperture, 'ISO': self.iso, 'S': self.speed, 'mm': self.focal}[text]
            return text if value else ''
        if text.startswith('@model='):
            return '' if 'version' in ident.lower() else self.camera
        if text.startswith('@location='):
            return (self.location_label or self.coordinates) if 'address' in text else self.coordinates
        if text.startswith('@time='):
            if 'yyyy' in text:
                # A separate calendar slot must not repeat the clock shown by
                # its neighbouring HH:mm node (several tag/Leica templates).
                if 'HH' in text:
                    return self.stamp
                return self.captured_at.strftime('%Y.%m.%d') if self.captured_at and self.date_enabled else ''
            dt = self.captured_at
            if dt is None:
                return self.stamp
            if text.endswith('_HH_mm'):
                return dt.strftime('%H:%M') if self.time_enabled else ''
            if text.endswith('_MM'):
                return dt.strftime('%m') if self.date_enabled else ''
            if text.endswith('_dd'):
                return dt.strftime('%d') if self.date_enabled else ''
            if text.endswith('_week'):
                return ('MON', 'TUE', 'WED', 'THU', 'FRI', 'SAT', 'SUN')[dt.weekday()] if self.date_enabled else ''
            if 'HH_mm' in text:
                return ' '.join(value for value in (
                    dt.strftime('%Y.%m.%d') if self.date_enabled else '',
                    dt.strftime('%H:%M') if self.time_enabled else '') if value)
            return dt.strftime('%Y.%m.%d') if self.date_enabled else ''
        if text.startswith('@exif='):
            if not self.parameters_enabled:
                return ''
            expr = text.split('=', 1)[1]
            if expr == '@{focal}mm  f/@{aperture}  @{speed}s  ISO@{iso}':
                return self.settings
            tokens = {'focal': self.focal, 'aperture': self.aperture, 'speed': self.speed, 'iso': self.iso}
            if any(not value for key, value in tokens.items() if '@{' + key + '}' in expr):
                return ''
            for key, value in tokens.items():
                expr = expr.replace('@{' + key + '}', value)
            return expr
        if text.startswith('@filter='):
            return self.filter_name
        if text.startswith('@custom='):
            return self.signature
        return text
