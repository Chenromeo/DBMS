from dataclasses import dataclass, field
from typing import List
import pickle


@dataclass
class TableMode:  # 字段名、字段类型、字段长、是否为key、是否允许为空、是否有效（可用于以后对表中该字段的删除）
    sFieldName: str
    sType: str
    # iSize: int
    bKey: bool = False
    bNullFlag: bool = False
    bValidFlag: bool = False


@dataclass
class TableSet:
    tableName: str
    tableMode: List[TableMode] = field(default_factory=list)
    modeinsert: List[list] = field(default_factory=list)


def print_table(table):
    print(f'表：{table.tableName}')
    for mode in table.tableMode:
        print(f'{mode.sFieldName:^20}', end=' ')
    print('')
    for data_list in table.modeinsert:
        for data in data_list:
            print(f'{data:^20}', end=' ')
        print('')


table1 = TableSet('学生', [TableMode('no', 'int'), TableMode('name', 'str')],
                  [['10180001', 'zy'], [10180002, 'zgp'], [10180003, 'zjl'], [10180004, 'lyh'], [10180005, 'cjy']])
print_table(table1)
print(type(table1.modeinsert[0][0]))
