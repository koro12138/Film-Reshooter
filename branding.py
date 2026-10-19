"""Product identity and one-time migration of the existing Windows preferences."""
from pathlib import Path
import sys

APP_NAME = 'Film Reshooter'
APP_VERSION = '1.0.0'
BUILD_VERSION = 'v14'
APP_TITLE = f'{APP_NAME} v{APP_VERSION}'

BRAND_CREDITS = '作者：b站@柳州市热心市民，@萬壹ZoveyOne'
BRAND_SOURCE = '滤镜水印来源：酷安@我的天啊ys'


def credits_html(muted='#b3b3b3'):
    """Two credit lines with theme-aware profile links."""
    style=f'color:{muted}; text-decoration:none'
    return ('作者：b站'
            f'<a href="https://space.bilibili.com/265409000" style="{style}">@柳州市热心市民</a>，'
            f'<a href="https://space.bilibili.com/496444830" style="{style}">@萬壹ZoveyOne</a><br>'
            '滤镜水印来源：酷安'
            f'<a href="https://www.coolapk.com/u/4153527" style="{style}">@我的天啊ys</a>')


def studio_settings(factory=None):
    from PySide6.QtCore import QSettings
    factory=factory or QSettings
    target = factory('FilmReshooter', 'Studio')
    if not target.contains('migration/cameralook_v1'):
        previous = factory('CameraLookDesktop', 'Studio')
        for key in previous.allKeys():
            if not target.contains(key):
                target.setValue(key, previous.value(key))
        target.setValue('migration/cameralook_v1', True)
        target.sync()
    return target


def icon_path(root):
    if sys.platform == 'darwin':
        return Path(root)/'assets/macos/FilmReshooter.icns'
    return Path(root)/'assets/branding/FilmReshooter.ico'
