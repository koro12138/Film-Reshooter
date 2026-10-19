"""Fluent-inspired Qt workspace: shared tokens, cards and task-focused pages.

Uses the existing Qt rendering/application controls; no web view or new runtime.
"""
from pathlib import Path
import sys
import re
from PySide6.QtCore import Qt,QSize,QRect,QEvent,QUrl
from PySide6.QtGui import QColor,QPainter,QPen,QFont,QIcon,QPixmap,QAction,QKeySequence,QDesktopServices
from PySide6.QtWidgets import (QWidget,QFrame,QLabel,QVBoxLayout,QHBoxLayout,QPushButton,
    QToolButton,QTabWidget,QTabBar,QScrollArea,QSplitter,QTableWidget,QHeaderView,QAbstractItemView,
    QListWidget,QListWidgetItem,QListView,QLineEdit,QCheckBox,QProgressBar,QStyledItemDelegate,
    QStyle,QSizePolicy,QApplication,QButtonGroup)

STYLE='''
QWidget { background:transparent; color:#f5f5f5; font-family:"Microsoft YaHei UI"; font-size:13px; }
QMainWindow, QWidget#workspace { background:#202020; }
QFrame#surface { background:#272727; border:1px solid #383838; border-radius:8px; }
QFrame#previewSurface { background:#171717; border:1px solid #383838; border-radius:8px; }
QFrame#card { background:#2d2d2d; border:1px solid #404040; border-radius:6px; }
QFrame#footer { background:#272727; border:1px solid #383838; border-radius:8px; }
QLabel#brand { font-family:"Segoe UI Variable","Segoe UI"; font-size:23px; font-weight:600; }
QLabel#brand[credits="true"] { font-size:11px; font-weight:400; color:#b3b3b3; }
QToolButton#logoButton { border:0; background:transparent; padding:0; }
QToolButton#logoButton:focus { border:0; background:transparent; }
QLabel#appIcon { background:#0f6cbd; border-radius:9px; color:white; font-size:21px; font-weight:600; }
QLabel#muted { color:#b3b3b3; font-size:12px; }
QLabel#section { color:#f5f5f5; font-size:15px; font-weight:600; }
QLabel#field { color:#dedede; font-size:13px; }
QLabel#badge { background:#173c59; color:#a8d9ff; border:1px solid #28587c; border-radius:12px; padding:4px 10px; font-size:12px; }
QLabel#count { background:#383838; border-radius:10px; color:#d6d6d6; padding:2px 8px; font-size:12px; }
QPushButton, QToolButton { background:#363636; border:1px solid #505050; border-bottom-color:#454545; border-radius:4px; padding:7px 11px; min-height:18px; }
QPushButton:hover, QToolButton:hover, QToolButton#queueView:hover { background:#404040; border-color:#626262; }
QPushButton:pressed, QToolButton:pressed { background:#303030; }
QPushButton:focus, QToolButton:focus { border:1px solid #85c5ff; }
QPushButton:checked { background:#173c59; border-color:#479ef5; color:#cbe6ff; }
QPushButton:disabled, QToolButton:disabled { color:#858585; background:#303030; border-color:#3c3c3c; }
QPushButton#primary { background:#0f6cbd; border-color:#3689d2; color:white; font-weight:600; padding:9px 18px; }
QPushButton#primary:hover { background:#1478ce; }
QPushButton#primary:pressed { background:#0e5b9c; }
QPushButton#primary:disabled { background:#3c3c3c; border-color:#454545; color:#929292; }
QPushButton#subtle, QToolButton#subtle { background:transparent; border-color:transparent; }
QPushButton#subtle:hover, QToolButton#subtle:hover { background:#3a3a3a; }
QPushButton#subtle:focus, QToolButton#subtle:focus { border-color:#85c5ff; }
QComboBox,QLineEdit,QSpinBox { background:#202020; color:#f5f5f5; border:1px solid #555555; border-bottom-color:#929292; border-radius:4px; min-height:18px; padding:7px 9px; selection-background-color:#0f6cbd; }
QComboBox:hover,QLineEdit:hover,QSpinBox:hover { background:#252525; }
QComboBox:focus,QLineEdit:focus,QSpinBox:focus { border-bottom:2px solid #60b4ff; }
QComboBox:disabled,QLineEdit:disabled,QSpinBox:disabled { color:#858585; border-color:#454545; background:#2b2b2b; }
QComboBox::drop-down { border:0; width:26px; }
QComboBox QAbstractItemView { background:#303030; border:1px solid #555555; padding:4px; selection-background-color:#174f79; outline:0; }
QTabWidget::pane { border:0; background:#272727; }
QTabBar::tab { background:transparent; color:#bdbdbd; padding:12px 12px; border-bottom:2px solid transparent; min-width:38px; }
QTabBar::tab:hover { color:#ffffff; background:#303030; }
QTabBar::tab:selected { color:#ffffff; border-bottom-color:#60b4ff; font-weight:600; }
QTabBar::tab:focus { background:#323232; }
QListWidget,QTableWidget { background:transparent; border:0; outline:0; selection-background-color:#173c59; }
QListWidget::item { border:0; }
QTableWidget::item { padding:5px; border:0; border-bottom:1px solid #383838; }
QTableWidget::item:hover { background:#333333; }
QTableWidget::item:selected { background:#173c59; color:#f5f5f5; }
QHeaderView::section { background:#272727; color:#bdbdbd; border:0; border-bottom:1px solid #404040; padding:9px 5px; font-size:12px; }
QScrollArea { background:transparent; border:0; }
QScrollBar:vertical { background:transparent; width:10px; margin:3px 1px; }
QScrollBar::handle:vertical { background:#666666; border-radius:3px; min-height:28px; margin:0 2px; }
QScrollBar::handle:vertical:hover { background:#929292; }
QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical { height:0; }
QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical { background:none; }
QSlider::groove:horizontal { background:#666666; height:4px; border-radius:2px; }
QSlider::sub-page:horizontal { background:#60b4ff; border-radius:2px; }
QSlider::handle:horizontal { background:#60b4ff; border:4px solid #454545; width:10px; height:10px; border-radius:9px; margin:-7px 0; }
QSlider::handle:horizontal:hover { background:#a8d9ff; }
QSlider:focus::handle:horizontal { border-color:#85c5ff; }
QCheckBox { spacing:8px; padding:4px 0; }
QCheckBox::indicator { width:16px; height:16px; }
QCheckBox:disabled { color:#858585; }
QProgressBar { background:#414141; border:0; border-radius:3px; min-height:6px; max-height:6px; color:transparent; }
QProgressBar::chunk { background:#60b4ff; border-radius:3px; }
QSplitter::handle { background:#202020; width:8px; }
QToolTip { background:#383838; color:#f5f5f5; border:1px solid #626262; padding:7px; }
QFrame#infoBar { background:#18372a; border:1px solid #376c4c; border-radius:6px; }
QFrame#infoBar[severity="warning"] { background:#41351a; border-color:#796534; }
QFrame#infoBar[severity="error"] { background:#432629; border-color:#94545b; }
QToolButton#queueView { background:transparent; border-color:transparent; padding:3px; min-height:16px; }
QToolButton#queueView:checked { background:#173c59; border-color:#479ef5; }
QToolButton#queueView:checked:hover { background:#174f79; border-color:#479ef5; }
QCheckBox#compactMulti { font-size:11px; spacing:5px; padding:0; }
QCheckBox#compactMulti::indicator { width:14px; height:14px; }
QLabel#strengthLabel { font-size:12px; }
QSpinBox#compactStrength { padding:3px 4px; font-size:12px; }
QSpinBox#compactStrength::up-button,QSpinBox#compactStrength::down-button,
QSpinBox#compactStrength::up-arrow,QSpinBox#compactStrength::down-arrow { width:0; height:0; border:0; image:none; }
QPushButton#inlineReset { padding:4px 6px; font-size:11px; min-height:18px; }
QFrame#footer QPushButton { padding:5px 8px; font-size:12px; min-height:18px; }
QLabel#metadata { color:#b3b3b3; font-size:11px; }
QProgressBar#footerProgress { min-width:6px; max-width:6px; min-height:36px; max-height:36px; }
'''

if sys.platform == 'darwin':
    STYLE = STYLE.replace('"Microsoft YaHei UI"', '"PingFang SC","Hiragino Sans GB"').replace('"Segoe UI Variable","Segoe UI"', '"Helvetica Neue","PingFang SC"')

DARK_PALETTE = {
    'window':'#202020','surface':'#272727','card':'#2d2d2d','preview':'#171717',
    'border':'#383838','border_soft':'#404040','text':'#f5f5f5','text_soft':'#dedede',
    'muted':'#b3b3b3','accent':'#60b4ff','accent_strong':'#0f6cbd','selection':'#173c59',
    'hover':'#303030','row_hover':'#393939','row_border':'#404040','row_border_hover':'#555555',
    'radio_bg':'#242424','radio_border':'#b3b3b3','focus':'#85c5ff',
}
LIGHT_PALETTE = {
    'window':'#f3f3f3','surface':'#ffffff','card':'#fafafa','preview':'#e6e6e6',
    'border':'#e2e2e2','border_soft':'#e9e9e9','text':'#1a1a1a','text_soft':'#2c2c2c',
    'muted':'#5d5d5d','accent':'#0f6cbd','accent_strong':'#0f6cbd','selection':'#dcecfa',
    'hover':'#efefef','row_hover':'#f1f1f1','row_border':'#e8e8e8','row_border_hover':'#c8c8c8',
    'radio_bg':'#ffffff','radio_border':'#8a8a8a','focus':'#0f6cbd',
}
# 深色样式表里的每个颜色都要有对应的浅色取值，缺一个就会在浅色下露出深色块。
LIGHT_MAP = {
    '#202020':'#f3f3f3', '#252525':'#ffffff', '#272727':'#ffffff', '#2b2b2b':'#f0f0f0',
    '#2d2d2d':'#fafafa', '#303030':'#ececec', '#323232':'#ececec', '#333333':'#f2f2f2',
    '#353535':'#eeeeee', '#363636':'#fdfdfd', '#383838':'#e2e2e2', '#3a3a3a':'#ececec',
    '#3a3f46':'#e6e6e6', '#3c3c3c':'#e8e8e8', '#404040':'#e9e9e9', '#414141':'#e3e3e3',
    '#454545':'#d2d2d2', '#505050':'#d6d6d6', '#555555':'#cfcfcf', '#565d66':'#c8c8c8',
    '#626262':'#b8b8b8', '#666666':'#c4c4c4', '#858585':'#9a9a9a', '#929292':'#8a8a8a',
    '#9aa3ad':'#5c5c5c', '#a3a3a3':'#8a8a8a', '#b3b3b3':'#5d5d5d', '#bdbdbd':'#5a5a5a',
    '#d6d6d6':'#333333', '#dedede':'#2c2c2c', '#f0f0f0':'#101010', '#f5f5f5':'#1a1a1a',
    '#ffffff':'#101010',
    '#171717':'#e6e6e6',
    '#0f6cbd':'#0f6cbd', '#1478ce':'#115ea3', '#0e5b9c':'#0c4a80', '#3689d2':'#0f6cbd',
    '#60b4ff':'#0f6cbd', '#85c5ff':'#0f6cbd', '#479ef5':'#0f6cbd',
    '#173c59':'#dcecfa', '#174f79':'#cfe6f8', '#a8d9ff':'#0b5a9e', '#28587c':'#a9d2ec',
    '#cbe6ff':'#0b4a85',
    '#18372a':'#e7f5ec', '#376c4c':'#9ed3b3', '#41351a':'#fdf3e2', '#796534':'#e0b567',
    '#432629':'#fdecec', '#94545b':'#e39a9a',
}
_SCHEME = 'dark'


def set_scheme(name):
    """Set the active palette; the stylesheet and custom painting both read it."""
    global _SCHEME
    _SCHEME = 'light' if str(name) == 'light' else 'dark'
    return _SCHEME


def current_scheme():
    return _SCHEME


def palette():
    return LIGHT_PALETTE if _SCHEME == 'light' else DARK_PALETTE


def color(name, fallback='#000000'):
    return palette().get(name, fallback)


_LIGHT_RE = re.compile('|'.join(sorted((re.escape(k) for k in LIGHT_MAP), key=len, reverse=True)), re.I)


def style_for(scheme='dark'):
    """Full stylesheet for a scheme; dark is the authored sheet, light is mapped."""
    if str(scheme) != 'light':
        return STYLE
    result=_LIGHT_RE.sub(lambda m: LIGHT_MAP[m.group(0).lower()], STYLE)
    for name in ('chevron-up','chevron-down'):result=result.replace(name+'.svg',name+'-light.svg')
    return result


_icons=(Path(getattr(sys,'_MEIPASS',Path(__file__).resolve().parent))/'assets/ui').as_posix()
STYLE+='''
QCheckBox::indicator:unchecked { background:#202020; border:1px solid #a3a3a3; border-radius:3px; }
QCheckBox::indicator:unchecked:hover { background:#353535; border-color:#ffffff; }
QCheckBox::indicator:checked { background:#0f6cbd; border:1px solid #60b4ff; border-radius:3px; image:url("ICONROOT/check.svg"); }
QCheckBox::indicator:disabled { border-color:#626262; }
QComboBox { padding-right:26px; }
QComboBox::down-arrow { image:url("ICONROOT/chevron-down.svg"); width:12px; height:12px; }
QSpinBox { padding-right:24px; }
QSpinBox::up-button { subcontrol-origin:border; subcontrol-position:top right; width:20px; border:0; }
QSpinBox::down-button { subcontrol-origin:border; subcontrol-position:bottom right; width:20px; border:0; }
QSpinBox::up-arrow { image:url("ICONROOT/chevron-up.svg"); width:9px; height:9px; }
QSpinBox::down-arrow { image:url("ICONROOT/chevron-down.svg"); width:9px; height:9px; }
'''.replace('ICONROOT',_icons)


def text(value,kind='field'):
    label=QLabel(value);label.setObjectName(kind);label.setWordWrap(True)
    return label


def queue_icon(done=False):
    icon=QIcon()
    for state in (QIcon.State.Off,QIcon.State.On):
        pixmap=QPixmap(32,32);pixmap.fill(Qt.GlobalColor.transparent)
        painter=QPainter(pixmap);painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        pen=QPen(QColor(color('accent' if state==QIcon.State.On else 'muted')),2.2)
        pen.setCapStyle(Qt.PenCapStyle.RoundCap);pen.setJoinStyle(Qt.PenJoinStyle.RoundJoin)
        painter.setPen(pen);painter.setBrush(Qt.BrushStyle.NoBrush);painter.drawEllipse(4,4,24,24)
        if done:
            painter.drawLine(10,16,14,20);painter.drawLine(14,20,23,11)
        else:
            painter.drawLine(16,9,16,16);painter.drawLine(16,16,21,19)
        painter.end();icon.addPixmap(pixmap,QIcon.Mode.Normal,state)
    return icon


def card(layout,title=None):
    frame=QFrame();frame.setObjectName('card')
    inside=QVBoxLayout(frame);inside.setContentsMargins(12,12,12,12);inside.setSpacing(8)
    if title:inside.addWidget(text(title,'section'))
    layout.addWidget(frame);return inside


def field(layout,title,control):
    label=text(title);label.setBuddy(control);control.setAccessibleName(title)
    layout.addWidget(label);layout.addWidget(control)


def page(tabs,title):
    area=QScrollArea();area.setWidgetResizable(True);area.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
    body=QWidget();layout=QVBoxLayout(body);layout.setContentsMargins(12,16,12,16);layout.setSpacing(12)
    area.setWidget(body);tabs.addTab(area,title);return layout


class InfoBar(QFrame):
    def __init__(self):
        super().__init__();self.setObjectName('infoBar');self.setProperty('severity','success')
        row=QHBoxLayout(self);row.setContentsMargins(12,6,8,6);row.setSpacing(12)
        self.message=text('');row.addWidget(self.message,1)
        self.details=QPushButton('查看记录');self.details.setObjectName('subtle');row.addWidget(self.details)
        close=QToolButton();close.setText('×');close.setObjectName('subtle');close.setAccessibleName('关闭通知')
        close.setToolTip('关闭通知');close.clicked.connect(self.hide);row.addWidget(close)
        self.hide()

    def show_message(self,message,severity='success',has_details=False):
        self.message.setText(message);self.setProperty('severity',severity)
        self.style().unpolish(self);self.style().polish(self)
        self.details.setVisible(has_details);self.show()


class FilterDelegate(QStyledItemDelegate):
    """Separate preview selection from the batch checkbox hit target."""
    @staticmethod
    def check_rect(rect):return QRect(rect.right()-26,rect.top()+10,18,18)

    def sizeHint(self,option,index):return self.parent().gridSize()

    def paint(self,painter,option,index):
        painter.save();painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        rect=option.rect.adjusted(4,4,-5,-5)
        selected=bool(option.state&QStyle.StateFlag.State_Selected)
        hover=bool(option.state&QStyle.StateFlag.State_MouseOver)
        painter.setPen(QPen(QColor(color('accent') if selected else color('row_border_hover') if hover else color('row_border')),2 if selected else 1))
        painter.setBrush(QColor(color('selection') if selected else color('row_hover') if hover else color('hover')))
        painter.drawRoundedRect(rect,6,6)
        image_height=min(146,max(24,rect.height()-49))
        image_rect=QRect(rect.x()+12,rect.y()+10,rect.width()-24,image_height)
        icon=index.data(Qt.ItemDataRole.DecorationRole)
        if isinstance(icon,QIcon):
            pix=icon.pixmap(QSize(104,156));size=pix.size();size.scale(image_rect.size(),Qt.AspectRatioMode.KeepAspectRatio)
            target=QRect(0,0,size.width(),size.height());target.moveCenter(image_rect.center())
            painter.setRenderHint(QPainter.RenderHint.SmoothPixmapTransform);painter.drawPixmap(target,pix)
        painter.setPen(QColor(color('text')));painter.setFont(option.font)
        painter.drawText(QRect(rect.x()+8,rect.y()+image_height+14,rect.width()-16,35),Qt.AlignmentFlag.AlignLeft|Qt.AlignmentFlag.AlignTop|Qt.TextFlag.TextWordWrap,index.data())
        if index.flags()&Qt.ItemFlag.ItemIsUserCheckable:
            check=self.check_rect(option.rect);checked=index.data(Qt.ItemDataRole.CheckStateRole)==Qt.CheckState.Checked.value
            painter.setBrush(QColor(color('accent_strong') if checked else color('radio_bg')));painter.setPen(QColor(color('focus') if checked else color('radio_border')))
            painter.drawRoundedRect(check,3,3)
            if checked:
                painter.setPen(QPen(QColor('white'),2));painter.drawLine(check.x()+4,check.y()+9,check.x()+8,check.y()+13)
                painter.drawLine(check.x()+8,check.y()+13,check.x()+14,check.y()+5)
        if option.state&QStyle.StateFlag.State_HasFocus:
            painter.setPen(QPen(QColor(color('text')),1,Qt.PenStyle.DotLine));painter.setBrush(Qt.BrushStyle.NoBrush)
            painter.drawRoundedRect(rect.adjusted(3,3,-3,-3),3,3)
        painter.restore()

    def editorEvent(self,event,model,option,index):
        if not index.flags()&Qt.ItemFlag.ItemIsUserCheckable:return False
        click=event.type()==QEvent.Type.MouseButtonRelease and event.button()==Qt.MouseButton.LeftButton and self.check_rect(option.rect).contains(event.position().toPoint())
        if click:
            checked=index.data(Qt.ItemDataRole.CheckStateRole)==Qt.CheckState.Checked.value
            return model.setData(index,Qt.CheckState.Unchecked if checked else Qt.CheckState.Checked,Qt.ItemDataRole.CheckStateRole)
        return False


class FilterList(QListWidget):
    def __init__(self,parent=None):
        super().__init__(parent)
        self.setVerticalScrollMode(QAbstractItemView.ScrollMode.ScrollPerPixel)
        self.verticalScrollBar().setSingleStep(20)

    def keyPressEvent(self,event):
        item=self.currentItem()
        if event.key()==Qt.Key.Key_Space and item and item.flags()&Qt.ItemFlag.ItemIsUserCheckable:
            item.setCheckState(Qt.CheckState.Unchecked if item.checkState()==Qt.CheckState.Checked else Qt.CheckState.Checked)
            event.accept();return
        super().keyPressEvent(event)



def pinned_page(tabs,title):
    holder=QWidget();vertical=QVBoxLayout(holder);vertical.setContentsMargins(0,0,0,0)
    fixed=QWidget();pinned=QVBoxLayout(fixed);pinned.setContentsMargins(12,12,12,4)
    vertical.addWidget(fixed)
    area=QScrollArea();area.setWidgetResizable(True)
    area.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
    body=QWidget();layout=QVBoxLayout(body);layout.setContentsMargins(12,8,12,16);layout.setSpacing(12)
    area.setWidget(body);vertical.addWidget(area,1);tabs.addTab(holder,title)
    return layout,pinned


RENDERED_ROLE=Qt.ItemDataRole.UserRole+1


class QueueDelegate(QStyledItemDelegate):
    """Fade photos with a completed preview, keeping selection and inspection."""
    def paint(self,painter,option,index):
        painter.save()
        if index.data(RENDERED_ROLE):painter.setOpacity(.68)
        super().paint(painter,option,index)
        painter.restore()


class EvenTabBar(QTabBar):
    def tabSizeHint(self,index):
        hint=super().tabSizeHint(index)
        return QSize(max(24,self.width()//max(1,self.count())),hint.height())


class EvenTabWidget(QTabWidget):
    def __init__(self,*args,**kwargs):
        super().__init__(*args,**kwargs)
        self.setTabBar(EvenTabBar(self))
        self.tabBar().setExpanding(True)
        self.tabBar().setDrawBase(False)
        self.tabBar().setUsesScrollButtons(False)
        self.tabBar().setElideMode(Qt.TextElideMode.ElideNone)

    def resizeEvent(self,event):
        super().resizeEvent(event)
        bar=self.tabBar()
        bar.setGeometry(0,0,self.width(),bar.sizeHint().height())


def build_workspace(w,ui):
    from branding import APP_NAME,APP_VERSION,credits_html,icon_path
    root=QWidget();root.setObjectName('workspace');w.setCentralWidget(root)
    layout=QVBoxLayout(root);w.workspace_layout=layout;layout.setContentsMargins(12,12,12,12);layout.setSpacing(12)
    header=QHBoxLayout();header.setSpacing(10)
    icon=QToolButton();icon.setObjectName('logoButton');icon.setFixedSize(40,40)
    icon.setIcon(QIcon(str(icon_path(ui.ROOT))));icon.setIconSize(QSize(40,40))
    icon.setCheckable(True);icon.setToolTip('显示作者与素材来源')
    icon.setCursor(Qt.CursorShape.PointingHandCursor)
    icon.setAccessibleName(APP_NAME+' 图标');header.addWidget(icon)
    w.brand=text(APP_NAME,'brand');w.brand.setWordWrap(False)
    w.brand.setSizePolicy(QSizePolicy.Policy.Ignored,QSizePolicy.Policy.Preferred)
    w.brand.setTextFormat(Qt.TextFormat.RichText)
    w.brand.setTextInteractionFlags(Qt.TextInteractionFlag.TextBrowserInteraction)
    w.brand.setOpenExternalLinks(False)
    w.brand.linkActivated.connect(lambda url:QDesktopServices.openUrl(QUrl(url)))
    header.addWidget(w.brand,1)
    def refresh_brand_links():
        w.brand.setText(credits_html(color('muted')) if icon.isChecked() else APP_NAME)
        w.brand.setProperty('credits',icon.isChecked())
        w.brand.style().unpolish(w.brand);w.brand.style().polish(w.brand)
    w.refresh_brand_links=refresh_brand_links
    icon.toggled.connect(lambda checked:refresh_brand_links())
    refresh_brand_links()
    header.addWidget(text('v'+APP_VERSION,'muted'));header.addStretch()
    w.hardware=text('默认 · Metal / CoreML' if sys.platform=='darwin' else '默认 · DirectML','badge');w.hardware.setWordWrap(False);header.addWidget(w.hardware)
    layout.addLayout(header);w.info_bar=InfoBar();layout.addWidget(w.info_bar)
    split=QSplitter(Qt.Orientation.Horizontal);w.workspace_split=split;split.setHandleWidth(6);layout.addWidget(split,1)

    left=QFrame();left.setObjectName('surface');left.setMinimumWidth(288);left.setMaximumWidth(360)
    ll=QVBoxLayout(left);w.queue_layout=ll;ll.setContentsMargins(12,16,12,12);ll.setSpacing(12)
    row=QHBoxLayout();row.setSpacing(4)
    queue_title=text('照片队列','section');queue_title.setWordWrap(False);row.addWidget(queue_title)
    row.addStretch()
    group=QButtonGroup(w);group.setExclusive(True)
    w.view_pending=QToolButton();w.view_done=QToolButton()
    for button,done,title in ((w.view_pending,False,'待导出'),(w.view_done,True,'已导出')):
        button.setObjectName('queueView');button.setFixedHeight(28)
        button.setSizePolicy(QSizePolicy.Policy.Minimum,QSizePolicy.Policy.Fixed)
        button.setIconSize(QSize(16,16));button.setIcon(queue_icon(done))
        button.setText(title);button.setToolButtonStyle(Qt.ToolButtonStyle.ToolButtonTextBesideIcon)
        button.setCheckable(True);button.setAccessibleName(title);button.setToolTip(title);group.addButton(button);row.addWidget(button)
    w.photo_count=text('0','count');row.addWidget(w.photo_count)
    w.view_pending.setChecked(True);ll.addLayout(row)
    row=QHBoxLayout();w.add_files=QPushButton('添加照片');w.add_folder=QPushButton('添加文件夹')
    w.add_files.setToolTip('添加照片（Ctrl+O）');w.add_folder.setToolTip('包含子文件夹（Ctrl+Shift+O）')
    row.addWidget(w.add_files);row.addWidget(w.add_folder);ll.addLayout(row)
    w.table=QTableWidget(0,2);w.table.setAccessibleName('照片队列');w.table.setIconSize(QSize(44,60))
    w.table.setHorizontalHeaderLabels(['照片','机型']);w.table.verticalHeader().hide()
    w.table.setItemDelegate(QueueDelegate(w.table))
    w.table.setSelectionBehavior(QAbstractItemView.SelectionBehavior.SelectRows)
    w.table.setSelectionMode(QAbstractItemView.SelectionMode.ExtendedSelection)
    w.table.setEditTriggers(QAbstractItemView.EditTrigger.NoEditTriggers);w.table.setShowGrid(False);w.table.setWordWrap(False)
    w.table.setVerticalScrollMode(QAbstractItemView.ScrollMode.ScrollPerPixel);w.table.verticalScrollBar().setSingleStep(20)
    w.table.horizontalHeader().setSectionResizeMode(0,QHeaderView.ResizeMode.Stretch)
    w.table.horizontalHeader().setSectionResizeMode(1,QHeaderView.ResizeMode.Fixed);w.table.setColumnWidth(1,88)
    w.table.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff);ll.addWidget(w.table,1)
    w.view_empty=text('','muted');w.view_empty.hide();ll.addWidget(w.view_empty)
    w.queue_label=text('拖入照片或文件夹即可开始','muted');ll.addWidget(w.queue_label)
    ll.addWidget(text('JPG、PNG、TIFF、HEIC 与相机 RAW','muted'))
    row=QHBoxLayout();w.remove=QPushButton('移除选中');w.clear=QPushButton('清空队列')
    for button in (w.remove,w.clear):button.setToolTip('仅移出队列，不删除原图')
    row.addWidget(w.remove);row.addWidget(w.clear);ll.addLayout(row);split.addWidget(left)

    center=QFrame();center.setObjectName('previewSurface');center.setMinimumWidth(200)
    cl=QVBoxLayout(center);w.preview_layout=cl;cl.setContentsMargins(16,16,16,16);cl.setSpacing(12)
    row=QHBoxLayout();w.preview_title=text('照片预览','section');w.preview_title.setWordWrap(False)
    w.preview_title.setSizePolicy(QSizePolicy.Policy.Ignored,QSizePolicy.Policy.Preferred);row.addWidget(w.preview_title,1)
    w.compare=QPushButton('查看原图');w.compare.setCheckable(True);row.addWidget(w.compare);cl.addLayout(row)
    w.canvas=ui.Canvas();w.canvas.setAccessibleName('照片效果预览');cl.addWidget(w.canvas,1)
    # Keep render notices available to the workflow without occupying the photo canvas.
    w.notice=text('预览采用缩略图；导出保留原始分辨率。','muted');w.notice.hide()
    split.addWidget(center)

    right=QFrame();right.setObjectName('surface');right.setMinimumWidth(320);right.setMaximumWidth(360)
    rl=QVBoxLayout(right);rl.setContentsMargins(0,0,0,0)
    w.settings_tabs=EvenTabWidget();w.settings_tabs.setAccessibleName('编辑设置');rl.addWidget(w.settings_tabs)
    fl=page(w.settings_tabs,'滤镜');w.filter_layout=fl;wl,pin=pinned_page(w.settings_tabs,'水印')
    el=page(w.settings_tabs,'导出');sl=page(w.settings_tabs,'设置')
    row=QHBoxLayout();row.setSpacing(6);row.addWidget(text('选择滤镜','section'));row.addStretch()
    w.multi=QCheckBox('每张照片导出多个滤镜');w.multi.setObjectName('compactMulti')
    w.multi.setToolTip('为每张照片导出多个滤镜；勾选后可选择多款滤镜');row.addWidget(w.multi)
    fl.addLayout(row)
    w.filter_search=QLineEdit();w.filter_search.setPlaceholderText('搜索滤镜名称…');w.filter_search.setClearButtonEnabled(True)
    w.filter_search.setAccessibleName('搜索滤镜');fl.addWidget(w.filter_search)
    w.select_all=QPushButton('全选 23 款 LUT / 清除勾选');w.select_all.hide();fl.addWidget(w.select_all)
    w.filters=FilterList();w.filters.setAccessibleName('滤镜预览与批量选择');w.filters.setViewMode(QListView.ViewMode.IconMode)
    w.filters.setResizeMode(QListView.ResizeMode.Adjust);w.filters.setMovement(QListView.Movement.Static);w.filters.setMouseTracking(True)
    w.filters.setIconSize(QSize(104,156));w.filters.setGridSize(QSize(136,204));w.filters.setWordWrap(True);w.filters.setUniformItemSizes(True)
    w.filters.setMinimumHeight(100);w.filters.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
    w.filters.setItemDelegate(FilterDelegate(w.filters))
    for preset in ui.CATALOG:
        item=QListWidgetItem(QIcon(str(ui.ROOT/'assets/previews/filters'/f"{preset['id']}.jpg")),f"{preset['id']+1:02d}  {preset['name']}")
        item.setToolTip(preset['name']+'\n固定范例，100% 强度；选择后预览当前照片')
        item.setCheckState(Qt.CheckState.Unchecked);item.setFlags(item.flags()&~Qt.ItemFlag.ItemIsUserCheckable);w.filters.addItem(item)
    w.filters.setCurrentRow(0);fl.addWidget(w.filters,1)
    w.filter_empty=text('没有匹配的滤镜','muted');w.filter_empty.hide();fl.addWidget(w.filter_empty)
    strength=card(fl);row=QHBoxLayout();row.setSpacing(6);w.strength_label=text('效果强度','strengthLabel');w.strength_label.setWordWrap(False);row.addWidget(w.strength_label)
    w.strength=ui.WheelSafeSlider(Qt.Orientation.Horizontal);w.strength.setRange(0,150);w.strength.setValue(100)
    w.strength.setAccessibleName('效果强度滑条');row.addWidget(w.strength,1)
    w.strength_value=ui.WheelSafeSpinBox();w.strength_value.setRange(0,150);w.strength_value.setValue(100)
    w.strength_value.setSuffix('%');w.strength_value.setFixedWidth(52);w.strength_value.setObjectName('compactStrength')
    w.strength_value.setAlignment(Qt.AlignmentFlag.AlignCenter);w.strength_value.setAccessibleName('效果强度数值')
    row.addWidget(w.strength_value)
    w.reset_strength=QPushButton('重置');w.reset_strength.setObjectName('inlineReset');w.reset_strength.setToolTip('将效果强度重置为 100%')
    w.reset_strength.setFixedWidth(42);row.addWidget(w.reset_strength);strength.addLayout(row)

    sample=card(pin);w.mark_sample=QLabel();w.mark_sample.setAlignment(Qt.AlignmentFlag.AlignCenter)
    w.mark_sample.setFixedHeight(156);w.mark_sample.setAccessibleName('水印静态样例');sample.addWidget(w.mark_sample)
    caption=text('样例预览','muted');caption.setAlignment(Qt.AlignmentFlag.AlignCenter);sample.addWidget(caption)
    w.style=ui.WheelSafeComboBox();w.style.setIconSize(QSize(30,40))
    for title,value in [('原有水印模板','original'),('经典白框','white'),('经典黑框','black'),('照片内叠加','overlay'),('不加水印','none')]:
        w.style.addItem(QIcon(str(ui.ROOT/'assets/previews/styles'/f'{value}.jpg')),title,value)
    field(wl,'水印类型',w.style)
    w.original_controls=QWidget();ol=QVBoxLayout(w.original_controls);ol.setContentsMargins(0,0,0,0);ol.setSpacing(8)
    w.mark_group=ui.WheelSafeComboBox()
    for key,value in ui.GROUP_NAMES.items():w.mark_group.addItem(value,key)
    w.mark_template=ui.WheelSafeComboBox();w.mark_variant=ui.WheelSafeComboBox();w.mark_background=ui.WheelSafeComboBox()
    def mark_row(name,control):
        holder=QWidget();inside=QVBoxLayout(holder);inside.setContentsMargins(0,0,0,0);inside.setSpacing(8)
        field(inside,name,control);ol.addWidget(holder);return holder
    w.mark_rows={}
    for name,control in [('系列',w.mark_group),('模板',w.mark_template),('版式',w.mark_variant),('背景',w.mark_background)]:
        control.setIconSize(QSize(30,40));w.mark_rows[name]=mark_row(name,control)
    w.mark_title=QLineEdit();w.mark_title.setMaxLength(100);w.mark_title.setPlaceholderText('留空则使用模板原文')
    w.title_row=mark_row('标题文字',w.mark_title)
    w.mark_note=text('','muted');ol.addWidget(w.mark_note);wl.addWidget(w.original_controls)
    w.mark_group.currentIndexChanged.connect(w.populate_templates);w.mark_template.currentIndexChanged.connect(w.populate_mark_options);w.populate_templates()
    info=card(wl,'照片信息')
    w.device=QCheckBox('显示机型');w.details=QCheckBox('拍摄参数（焦距、光圈、快门、ISO）')
    w.date=QCheckBox('拍摄日期');w.time=QCheckBox('拍摄时间');w.location=QCheckBox('GPS 经纬度');w.caption=QCheckBox('滤镜名称')
    for check in (w.device,w.details,w.date,w.time,w.location,w.caption):check.setChecked(True);info.addWidget(check)
    w.caption.setChecked(False)
    for check in (w.device,w.details,w.date,w.time,w.location,w.caption):
        check.setToolTip('同时控制模板原有文字、附加信息、照片预览与导出；不修改文件内 EXIF。')
    w.supplement_information=QCheckBox('补充模板缺少的信息');w.supplement_information.setChecked(True)
    w.supplement_information.setToolTip('只补充当前模板未显示的日期、时间、机型和经纬度，已有内容不会重复。关闭后不增加附加小字；模板原有文字仍由上方开关控制。')
    info.addWidget(w.supplement_information)
    w.style.currentIndexChanged.connect(lambda:w.supplement_information.setEnabled(not w._batch_busy and w.style.currentData()=='original'))
    info.addWidget(text('信息自动读取 EXIF。原有模板只补缺失项；附加小字跟随原色和对齐，不扩展画布。','muted'));wl.addStretch()

    fmt=card(el,'输出文件');w.fmt=ui.WheelSafeComboBox();w.fmt.addItems(['JPEG','PNG','TIFF 16-bit','PNG 16-bit','Ultra HDR JPEG'])
    field(fmt,'文件格式',w.fmt)
    w.export_quality=ui.WheelSafeSpinBox();w.export_quality.setRange(70,100);w.export_quality.setValue(97);field(fmt,'本次 JPEG 质量',w.export_quality)
    w.export_quality_note=text('沿用设置页的默认质量','muted');fmt.addWidget(w.export_quality_note)
    w.save_mode=ui.WheelSafeComboBox();w.save_mode.addItem('常规压缩 · 较小文件','normal');w.save_mode.addItem('快速保存 · 较大文件','fast')
    if ui.os.environ.get('CAMERALOOK_FAST_SAVE')=='1':w.save_mode.setCurrentIndex(1)
    w.save_mode.setToolTip('JPEG 质量与采样率不变；PNG 像素不变。快速保存通常增大文件。TIFF / Ultra HDR 不受此项影响。')
    field(fmt,'保存模式',w.save_mode)
    used=card(el,'自定义信息');w.use_custom=QCheckBox('使用自定义信息');w.use_custom.setChecked(True);used.addWidget(w.use_custom)
    w.custom_switches=QWidget();sub=QVBoxLayout(w.custom_switches);sub.setContentsMargins(18,0,0,0)
    w.use_model=QCheckBox('拍摄机型');w.use_signature=QCheckBox('署名 / 模板文字');w.use_location=QCheckBox('地点名称');w.use_signature_image=QCheckBox('签名图片')
    for check in (w.use_model,w.use_signature,w.use_location,w.use_signature_image):check.setChecked(True);sub.addWidget(check)
    w.use_signature.setChecked(False);w.use_location.setChecked(False)
    w.use_model.setToolTip('仅启用设置页填写的备用或覆盖机型；水印页的“显示机型”控制是否显示。')
    w.use_location.setToolTip('仅控制手工地点名称，与水印页的 GPS 经纬度开关独立。')
    w.use_signature.setToolTip('仅显示填写的署名，不会自动替换成滤镜名称。')
    used.addWidget(w.custom_switches);used.addWidget(text('在设置页填写内容；此处仅控制是否用于本次导出与预览。','muted'))
    el.addWidget(text('导出处理整个队列。16-bit 保留高位深；Ultra HDR 需要兼容的查看器与屏幕。','muted'));el.addStretch()

    defaults=card(sl,'导出默认值')
    w.output=QLineEdit(str(w.settings.value('output',str(Path.home()/'Pictures'/'FilmReshooter输出'))));field(defaults,'保存位置',w.output)
    w.choose_destination=QPushButton('选择文件夹…');w.choose_destination.clicked.connect(w.choose_output);defaults.addWidget(w.choose_destination)
    w.quality=ui.WheelSafeSpinBox();w.quality.setRange(70,100)
    try:w.quality.setValue(int(w.settings.value('quality',97)))
    except (TypeError,ValueError):w.quality.setValue(97)
    field(defaults,'默认 JPEG 质量',w.quality)
    w.keep_exif=QCheckBox('保留拍摄信息\n（包括原有 GPS EXIF）')
    w.keep_exif.setAccessibleName('保留拍摄信息（包括原有 GPS EXIF）')
    w.keep_exif.setToolTip('保留拍摄信息，包括原有 GPS EXIF')
    w.keep_exif.setChecked(str(w.settings.value('keep_exif','1')).strip().lower() not in ('0','false','no','off',''));defaults.addWidget(w.keep_exif)
    appearance=card(sl,'外观');w.theme=ui.WheelSafeComboBox()
    for title,value in [('跟随系统','system'),('浅色','light'),('深色','dark')]:w.theme.addItem(title,value)
    field(appearance,'主题',w.theme)
    mark_defaults=card(sl,'水印默认值');w.default_title=QLineEdit();w.default_title.setMaxLength(100)
    w.default_title.setPlaceholderText('留空则使用模板原文');field(mark_defaults,'默认标题文字',w.default_title)
    w.leica_mark=QCheckBox('显示徕卡标识');w.leica_mark.setChecked(True)
    w.leica_mark.setToolTip('控制原有模板中的徕卡 Logo 等标识；保留机型、拍摄参数、时间和位置')
    mark_defaults.addWidget(w.leica_mark)
    w.show_brand=QCheckBox('设备名称包含品牌');w.show_brand.setChecked(True);mark_defaults.addWidget(w.show_brand)
    custom=card(sl,'自定义信息')
    w.fallback=QLineEdit();w.fallback.setMaxLength(150);w.fallback.setPlaceholderText('仅在 EXIF 缺失时补充');field(custom,'拍摄机型',w.fallback)
    w.override=QCheckBox('用此机型覆盖所有照片');custom.addWidget(w.override)
    w.signature=QLineEdit();w.signature.setMaxLength(100);field(custom,'署名 / 模板文字',w.signature)
    w.location_label=QLineEdit();w.location_label.setMaxLength(100);field(custom,'地点名称',w.location_label)
    w.signature_image=QLineEdit();field(custom,'签名图片',w.signature_image)
    w.signature_choose=QPushButton('选择签名图片…')
    def choose_signature():
        path,_=ui.QFileDialog.getOpenFileName(w,'选择签名图片','','图片 (*.png *.webp *.jpg)')
        if path:w.signature_image.setText(path)
    w.signature_choose.clicked.connect(choose_signature);custom.addWidget(w.signature_choose)
    perf=card(sl,'渲染方式');w.backend=ui.WheelSafeComboBox()
    from edition import nvidia_supported
    backends=[('默认 · DirectML','auto'),('CPU','cpu'),('GPU · DirectML / OpenGL','gpu')]
    if sys.platform=='darwin':backends=[('默认 · Metal / CoreML','auto'),('CPU · 精确参考','cpu'),('GPU · Metal / CoreML','gpu')]
    if nvidia_supported():backends.append(('NVIDIA · 实验性 M9 加速','nvidia'))
    for title,value in backends:w.backend.addItem(title,value)
    if nvidia_supported() and ui.os.environ.get('CAMERALOOK_EXPERIMENTAL_NVIDIA')=='1':w.backend.setCurrentIndex(w.backend.findData('nvidia'))
    w.backend.setAccessibleName('渲染后端');perf.addWidget(w.backend)
    if sys.platform=='darwin':
        w.m9_coreml=QCheckBox('M9 使用 CoreML 加速');perf.addWidget(w.m9_coreml)
        w.m9_warm=QCheckBox('启动时后台预编译 M9 模型');perf.addWidget(w.m9_warm)
        perf.addWidget(text('Metal 用于图像处理；CoreML 按系统调度使用 CPU、GPU 或 ANE。CoreML 与精确 CPU 推理可能有小幅差异，首次编译需要时间。','muted'))
    else:
        perf.addWidget(text('默认使用 DirectML，失败回退 CPU。'+('NVIDIA 仅供手动实验，首次可能需要编译。' if nvidia_supported() else '标准版不包含 NVIDIA 专用实验后端。'),'muted'))
    sl.addStretch()
    split.addWidget(right);split.setSizes([288,776,328]);split.setStretchFactor(1,1)
    for i in range(3):split.setCollapsible(i,False)

    footer=QFrame();w.footer=footer;footer.setObjectName('footer');footer.setMinimumHeight(68)
    row=QHBoxLayout(footer);row.setContentsMargins(0,0,0,0);row.setSpacing(split.handleWidth())
    w.footer_status=QWidget();status=QVBoxLayout(w.footer_status);status.setContentsMargins(12,8,8,8);status.setSpacing(4)
    w.status=text('添加照片，开始预览');w.status.setWordWrap(False)
    w.status.setSizePolicy(QSizePolicy.Policy.Ignored,QSizePolicy.Policy.Preferred)
    w.export_summary=text('队列为空','muted');status.addWidget(w.status);status.addWidget(w.export_summary);row.addWidget(w.footer_status)
    w.footer_metadata=QWidget();w.footer_metadata.setSizePolicy(QSizePolicy.Policy.Ignored,QSizePolicy.Policy.Preferred)
    meta=QVBoxLayout(w.footer_metadata);meta.setContentsMargins(8,8,8,8)
    w.metadata=text('拍摄机型、参数、时间与位置会显示在这里。','metadata')
    w.metadata.setAlignment(Qt.AlignmentFlag.AlignCenter);w.metadata.setWordWrap(True);w.metadata.setTextFormat(Qt.TextFormat.PlainText)
    metadata_policy=QSizePolicy(QSizePolicy.Policy.Ignored,QSizePolicy.Policy.Preferred);metadata_policy.setHeightForWidth(True)
    w.metadata.setSizePolicy(metadata_policy);meta.addWidget(w.metadata)
    row.addWidget(w.footer_metadata,1)
    w.footer_actions=QWidget();actions=QHBoxLayout(w.footer_actions);actions.setContentsMargins(8,8,12,8);actions.setSpacing(6)
    w.progress=QProgressBar();w.progress.setObjectName('footerProgress');w.progress.setOrientation(Qt.Orientation.Vertical)
    w.progress.setRange(0,100);w.progress.setValue(0);w.progress.setTextVisible(False);actions.addWidget(w.progress)
    w.progress_percent=text('0%','muted');w.progress_percent.setFixedWidth(28);w.progress_percent.setWordWrap(False);actions.addWidget(w.progress_percent)
    w.open_output=QPushButton('打开输出');w.cancel=QPushButton('取消');w.cancel.setEnabled(False);w.cancel.hide()
    w.export=QPushButton('批量导出');w.export.setObjectName('primary');w.export.setToolTip('导出整个照片队列（Ctrl+Enter）')
    w.open_output.setFixedWidth(72);w.cancel.setFixedWidth(48);w.export.setMinimumWidth(108)
    for button in (w.open_output,w.cancel,w.export):actions.addWidget(button)
    row.addWidget(w.footer_actions)
    layout.addWidget(footer);w.info_bar.details.clicked.connect(w.open_export_log)
    w.strength.valueChanged.connect(w.strength_value.setValue);w.strength_value.valueChanged.connect(w.strength.setValue)
    w.reset_strength.clicked.connect(lambda:w.strength.setValue(100))
    w.multi.toggled.connect(w.set_multi_mode);w.filters.itemChanged.connect(w.refresh_export_state);w.filters.currentRowChanged.connect(w.refresh_export_state)
    w.table.itemSelectionChanged.connect(w.refresh_export_state);w.filter_search.textChanged.connect(w.search_filters)
    w.progress.valueChanged.connect(lambda value:w.progress_percent.setText(f'{value}%'))
    for shortcut,callback in [('Ctrl+O',w.choose_files),('Ctrl+Shift+O',w.choose_folder),('Ctrl+Return',w.start_export)]:
        action=QAction(w);action.setShortcut(QKeySequence(shortcut));action.triggered.connect(callback);w.addAction(action)
    action=QAction(w.table);action.setShortcut(QKeySequence('Delete'));action.setShortcutContext(Qt.ShortcutContext.WidgetWithChildrenShortcut)
    action.triggered.connect(w.remove_selected);w.table.addAction(action)
    w._batch_busy=False;w._export_log='';w.refresh_export_state()


def adapt_workspace(w):
    """Keep the familiar sidebar widths; reclaim vertical space on short screens."""
    compact=w.height()<640
    if getattr(w,'_compact_workspace',None)==compact:return
    w._compact_workspace=compact
    gap=6 if compact else 12
    w.workspace_layout.setContentsMargins(8 if compact else 12,8 if compact else 12,8 if compact else 12,8 if compact else 12)
    w.workspace_layout.setSpacing(gap)
    w.queue_layout.setContentsMargins(12,8 if compact else 16,12,8 if compact else 12)
    w.queue_layout.setSpacing(gap)
    margin=8 if compact else 16
    w.preview_layout.setContentsMargins(margin,margin,margin,margin)
    w.preview_layout.setSpacing(gap)
    w.filter_layout.setContentsMargins(12,8 if compact else 16,12,8 if compact else 16)
    w.filter_layout.setSpacing(8 if compact else 12)
    w.filters.setGridSize(QSize(136,120 if compact else 204))
    w.filters.setMinimumHeight(88 if compact else 100)
    w.filters.setSizePolicy(QSizePolicy.Policy.Expanding,QSizePolicy.Policy.Ignored if compact else QSizePolicy.Policy.Expanding)
    w.mark_sample.setFixedHeight(80 if compact else 156)
    w.update_mark_sample()
