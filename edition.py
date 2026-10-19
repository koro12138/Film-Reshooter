"""Frozen build capabilities; source checkouts support the complete toolset."""
from pathlib import Path
import json
import sys

ROOT=Path(getattr(sys,'_MEIPASS',Path(__file__).resolve().parent))


def _configuration():
    path=ROOT/'release_edition.json'
    if path.is_file():return json.loads(path.read_text('utf-8'))
    return {'edition':'source','nvidia':not getattr(sys,'frozen',False)}


CONFIG=_configuration()


def nvidia_supported():return sys.platform == 'win32' and CONFIG.get('nvidia') is True


def edition_name():return CONFIG.get('edition','standard')
