import pymysql,tkinter
from tkinter import messagebox

conn = pymysql.connect(host="localhost", user="root", password="111111", port=3306, database="police_case", charset="utf8")
if conn:
    print("connect success")


def sql_execute(sql):
    print(sql)
    cur = conn.cursor()
    cur.execute(sql)
    conn.commit()


def search(sql_query):
    print(sql_query)
    search_page = tkinter.Tk()
    search_page.title("查询结果")
    search_page.geometry("600x400")
    scx = tkinter.Scrollbar(search_page, orient=tkinter.HORIZONTAL)
    scx.pack(side=tkinter.BOTTOM, fill=tkinter.X)
    scy = tkinter.Scrollbar(search_page)
    scy.pack(side=tkinter.RIGHT, fill=tkinter.Y)
    show_listbox = tkinter.Listbox(search_page, width=40)
    show_listbox['xscrollcommand'] = scx.set
    show_listbox['yscrollcommand'] = scy.set
    scx['command'] = show_listbox.xview
    scy['command'] = show_listbox.yview
    show_listbox.pack(expand=True)
    cur = conn.cursor()
    cur.execute(sql_query)
    data = cur.fetchall()
    for item in data:
        show_listbox.insert(tkinter.END, item)
    search_page.mainloop()


def update():
    update_page = tkinter.Tk()
    update_page.title("更新操作页面")
    update_page.geometry("600x400")
    table_name_label = tkinter.Label(update_page, text="表名")
    table_name_label.grid(row=0, column=0)
    table_name_entry = tkinter.Entry(update_page, width=50)
    table_name_entry.grid(row=0, column=1)
    attribute_name_label = tkinter.Label(update_page, text='修改的属性')
    attribute_name_label.grid(row=1, column=0)
    attribute_name_entry = tkinter.Entry(update_page, width=50)
    attribute_name_entry.grid(row=1, column=1)
    set_value_label = tkinter.Label(update_page, text="希望修改成的值")
    set_value_label.grid(row=2, column=0)
    set_value_entry = tkinter.Entry(update_page, width=50)
    set_value_entry.grid(row=2, column=1)
    requirement_label = tkinter.Label(update_page, text="条件")
    requirement_label.grid(row=3, column=0)
    requirement_entry = tkinter.Entry(update_page, width=50)
    requirement_entry.grid(row=3, column=1)
    show_lb = tkinter.Listbox(update_page, width=40)
    show_lb.grid(row=5, columnspan=2)
    update_sql = ""

    def show_sql():
        nonlocal update_sql
        update_sql=""
        show_lb.delete(0,tkinter.END)
        show_lb.insert(tkinter.END, "Update " + table_name_entry.get() + '\n')
        update_sql += "update test." + table_name_entry.get()
        show_lb.insert(tkinter.END, "Set " + attribute_name_entry.get() + "=" + set_value_entry.get() + '\n')
        update_sql += " set " + attribute_name_entry.get() + "=" + set_value_entry.get()
        show_lb.insert(tkinter.END, "where " + requirement_entry.get())
        update_sql += " where " + requirement_entry.get()

    preview_button = tkinter.Button(update_page, text="预览sql语句", command=show_sql)
    preview_button.grid(row=4, columnspan=2)
    exec_button = tkinter.Button(update_page, text="执行", command=lambda: sql_execute(update_sql))
    exec_button.grid(row=5)


def insert():
    insert_page = tkinter.Tk()
    insert_page.title("插入操作页面")
    insert_page.geometry("600x200")
    table_name_label = tkinter.Label(insert_page, text="表名")
    table_name_label.grid(row=0, column=0)
    table_name_entry = tkinter.Entry(insert_page, width=50)
    table_name_entry.grid(row=0, column=1)
    attribute_name_label = tkinter.Label(insert_page, text='插入的元组')
    attribute_name_label.grid(row=1, column=0)
    attribute_name_entry = tkinter.Entry(insert_page, width=50)
    attribute_name_entry.grid(row=1, column=1)
    insert_sql = ""


def delete():
    delete_page = tkinter.Tk()
    delete_page.title("插入操作页面")
    delete_page.geometry("600x200")
    table_name_label = tkinter.Label(delete_page, text="表名")
    table_name_label.grid(row=0, column=0)
    table_name_entry = tkinter.Entry(delete_page, width=50)
    table_name_entry.grid(row=0, column=1)
    attribute_name_label = tkinter.Label(delete_page, text='删除的元组')
    attribute_name_label.grid(row=1, column=0)
    attribute_name_entry = tkinter.Entry(delete_page, width=50)
    attribute_name_entry.grid(row=1, column=1)
    insert_sql = ""


def show_info_about():
    messagebox.showinfo("关于我们", "小组成员:\n  计181 陈俊咏 \n  计181 李元昊  \n  计181 赵奕\n  "
                                "计181 张国鹏\n  计181 周嘉磊")


root = tkinter.Tk()
root.geometry("800x300")
root.title("窗口化数据库系统")
#  menubar 部分
menubar = tkinter.Menu(root)
menu = tkinter.Menu(menubar, tearoff=False)
menu.add_command(label="插入", command=insert)
menu.add_command(label="更新", command=update)
menu.add_command(label="删除", command=delete)
menubar.add_cascade(label="操作", menu=menu)
menubar.add_command(label="关于", command=show_info_about)
menubar.add_command(label="退出", command=root.quit)
root.config(menu=menubar)
#  root 主界面
sql_label = tkinter.Label(root, text="输入sql语句")
sql_entry = tkinter.Entry(root, width=60)
sql_label.grid(row=0, column=0)
sql_entry.grid(row=0, column=1)
sql = sql_entry.get()
button = tkinter.Button(root, text="执行", command=lambda: search(sql_entry.get()))
button.grid(row=0, column=2)
root.mainloop()
