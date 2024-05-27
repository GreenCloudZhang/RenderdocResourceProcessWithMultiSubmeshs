'''
mesh 数据导出为 CSV 文件
'''

import os, csv, sys
from pathlib import Path

from PySide2 import QtWidgets, QtCore, QtGui

current_folder = Path(__file__).absolute().parent
father_folder = str(current_folder.parent)
sys.path.append(father_folder)

from qt_utilities.progress_bar_utility import ProgressBarUtility
from fbx_res.fbx_export_option_dialog_const_mapper import FbxExportOptionDialogConstMapper as FCM


class MeshToCsv:

    emgr = None

    def __init__(self, emgr_):
        self.emgr = emgr_
        pass

    def get_arg(self, config_, key_):
        if config_.get(key_):
            return config_[key_]
        else:
            return '0'
        pass

    def execute(self, table_, save_path_, alias_config_):
        name_pos = self.get_arg(alias_config_, FCM.c_export_pos)
        name_normal = self.get_arg(alias_config_, FCM.c_export_normal)
        name_tangent = self.get_arg(alias_config_, FCM.c_export_tangent)
        name_color = self.get_arg(alias_config_, FCM.c_export_color)
        name_uv = self.get_arg(alias_config_, FCM.c_export_uv)
        name_uv2 = self.get_arg(alias_config_, FCM.c_export_uv2)
        name_uv3 = self.get_arg(alias_config_, FCM.c_export_uv3)

        # 先把旧的删掉
        if os.path.exists(save_path_):
            os.remove(save_path_)

        model = table_.model()
        row_count = model.rowCount()
        column_count = model.columnCount()
        rows = range(row_count)
        columns = range(column_count)

        head_names = list()
        row_data_list = list()

        for _, c_i in ProgressBarUtility.loop(columns, status_='Collect mesh data'):
            head = model.headerData(c_i, QtCore.Qt.Horizontal)
            row_data = [model.data(model.index(r_i, c_i)) for r_i in rows]

            rename_head = head
            if(head.find(name_pos)!=-1):
                rename_head = head.replace(name_pos, "POSITION")
            if(head.find(name_normal)!=-1):
                rename_head = head.replace(name_normal, "NORMAL")
            if(head.find(name_tangent)!=-1):
                rename_head = head.replace(name_tangent, "TANGENT")
            if(head.find(name_color)!=-1):
                rename_head = head.replace(name_color, "COLOR")
            if(head.find(name_uv)!=-1):
                rename_head = head.replace(name_uv, "TEXCOORD0")
            if(head.find(name_uv2)!=-1):
                rename_head = head.replace(name_uv2, "TEXCOORD1")
            if(head.find(name_uv3)!=-1):
                rename_head = head.replace(name_uv3, "TEXCOORD2")
            #rename_head = name_pos
            head_names.append(rename_head)
            row_data_list.append(row_data)

        with open(save_path_, "w", newline='') as csvFile:
            writer = csv.writer(csvFile)
            writer.writerow(head_names)

            for _, r_i in ProgressBarUtility.loop(rows, status_='Write to the csv file'):
                write_data = list()
                for row_data in row_data_list:
                    row_item = row_data[r_i]
                    write_data.append(row_item)
                writer.writerow(write_data)

        pass
