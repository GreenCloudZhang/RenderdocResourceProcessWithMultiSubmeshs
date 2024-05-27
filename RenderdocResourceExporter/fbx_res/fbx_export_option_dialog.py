'''
FBX 导出选项设置窗
'''

import os
import sys
from pathlib import Path
from functools import partial

from PySide2 import QtWidgets, QtCore, QtGui

current_folder = Path(__file__).absolute().parent
father_folder = str(current_folder.parent)
sys.path.append(father_folder)

from qt_utilities.setting_utility import SettingUtility
from qt_utilities.root_const_mapper import RootConstMapper as RCM
from fbx_res.fbx_export_option_dialog_const_mapper import FbxExportOptionDialogConstMapper as FCM


class FbxExportOptionDialog:

    emgr = None
    mqt = None

    default_config = [
        FCM.c_export_normal,
        FCM.c_export_tangent,
        FCM.c_export_color,
        FCM.c_export_uv,
        FCM.c_export_uv2,
        FCM.c_export_uv3,
    ]
    option_widget_dict = {}

    necessary_widget_dict = {}

    export_config = {}

    alias_config = {}


    def __init__(self, emgr_):
        self.emgr = emgr_
        self.mqt = emgr_.GetMiniQtHelper()

        path, self.settings = SettingUtility.get_tempdir_setting(RCM.setting_preference)
        if not os.path.exists(path):
            self.refresh_option(0)
        pass

    def refresh_option(self, index_):
        if hasattr(self, "language"):
            language = self.language.itemText(index_)
        else:
            language = RCM.c_en
        self.settings.setValue(RCM.c_language, language)

        # 刷新ui显示
        if hasattr(self, "language_label"):
            self.mqt.SetWidgetText(self.language_label, FCM.get_text(FCM.c_language))

        for key, widget in self.option_widget_dict.items():
            self.mqt.SetWidgetText(widget.label, FCM.get_text(key))
        pass

    def init_ui(self):
        # 这里暂时没找到动态修改的方法，全靠每次重启了
        self.widget = self.mqt.CreateToplevelWidget(FCM.get_text(FCM.c_dialog_title), None)

        # 语言选项
        language_container = self.mqt.CreateHorizontalContainer()

        self.language_label = self.mqt.CreateLabel()
        self.mqt.SetWidgetText(self.language_label, FCM.get_text(FCM.c_language))

        self.language = QtWidgets.QComboBox()
        self.language.addItems([RCM.c_en, RCM.c_cn])
        self.language.setCurrentText(self.settings.value(RCM.c_language, RCM.c_en))
        self.language.currentIndexChanged.connect(self.refresh_option)

        self.mqt.AddWidget(language_container, self.language_label)
        self.mqt.AddWidget(language_container, self.language)
        self.mqt.AddWidget(self.widget, language_container)

        # position导出别名
        pos_key = FCM.c_export_pos
        pWidget = self.necessary_widget(pos_key)
        self.mqt.AddWidget(self.widget, pWidget)
        self.necessary_widget_dict[pos_key] = pWidget
        self.mqt.SetWidgetText(pWidget.label, FCM.get_text(pos_key))

        # 创建勾选项
        for key in self.default_config:
            widget = self.option_widget(key)
            self.mqt.AddWidget(self.widget, widget)
            self.option_widget_dict[key] = widget

            self.mqt.SetWidgetText(widget.label, FCM.get_text(key))
            self.mqt.SetWidgetChecked(widget.edit, True)

        # 按钮
        button_container = self.mqt.CreateHorizontalContainer()

        callback = lambda *args: self.mqt.CloseCurrentDialog(False)
        cancel_button = self.mqt.CreateButton(callback)
        self.mqt.SetWidgetText(cancel_button, FCM.get_text(FCM.c_cancel))

        ok_button = self.mqt.CreateButton(self.button_accept)
        self.mqt.SetWidgetText(ok_button, FCM.get_text(FCM.c_ok))

        self.mqt.AddWidget(button_container, cancel_button)
        self.mqt.AddWidget(button_container, ok_button)
        self.mqt.AddWidget(self.widget, button_container)

        return self.widget
    
    #选项修改时
    def line_change(self, text_):
        self.alias_config[FCM.c_export_pos]=text_
        pass

    def necessary_widget(self, key_):
        container = self.mqt.CreateHorizontalContainer()
        label = self.mqt.CreateLabel()
        alias = QtWidgets.QLineEdit()
        alias.setText("NULL")
        #alias.textEdited.connect(self.line_change)
        self.mqt.AddWidget(container, label)
        self.mqt.AddWidget(container, alias)
        container.label = label
        container.alias = alias
        return container

    #选项的组件
    def option_widget(self, key_):
        container = self.mqt.CreateHorizontalContainer()

        label = self.mqt.CreateLabel()
        edit = self.mqt.CreateCheckbox(partial(self.option_change, key_))
        #alias = self.mqt.CreateTextBox(True, partial(self.text_change, key_))
        alias = QtWidgets.QLineEdit()
        alias.setText("NULL")
        #alias.textEdited.connect(self.line_change)

        self.mqt.AddWidget(container, label)
        self.mqt.AddWidget(container, edit)
        self.mqt.AddWidget(container, alias)

        container.label = label
        container.edit = edit
        container.alias = alias

        return container

    #选项修改时
    def option_change(self, key_, context_, widget_, text_):
        pass

    #选项修改时
    def text_change(self, key_, context_, widget_, text_):
        self.mqt.SetWidgetText(widget_, text_)
        pass

    #按钮确认
    def button_accept(self, context_, widget_, text_):
        for key, widget in self.option_widget_dict.items():
            value = self.mqt.IsWidgetChecked(widget.edit)
            self.export_config[key] = value
            name = widget.alias.text()
            self.alias_config[key] = name
        for key, widget in self.necessary_widget_dict.items():
            name = widget.alias.text()
            self.alias_config[key] = name
        self.mqt.CloseCurrentDialog(True)
        pass
