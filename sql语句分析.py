import sqlparse
import re

sql = "select id,name_,age from dual where a=b union;" \
      "insert into c values(a,b,c)"
# 1.分割SQL
stmts = sqlparse.split(sql)
print('split:\n', stmts, '\n')
print('-'*100)
for stmt in stmts:
    # 2.format格式化
    print('format:\n', sqlparse.format(stmt, reindent=True, keyword_case="upper"))  # 关键字大写,修改缩进
    # 3.解析SQL
    stmt_parsed = sqlparse.parse(stmt)
    print('\nparse:\n', stmt_parsed[0].tokens, '\n')
    for i in stmt_parsed[0].tokens:
        print(i, '\t      ttype:', i.ttype)
        print(' \t             type: ', type(i), '\n')
    print('-'*100)

    print(re.search('update', sql))
    print(re.search('insert', sql))
    print(re.search('delete', sql))
    parsed = sqlparse.parse(sql)
    result = sqlparse.sql.Statement(parsed[0].tokens)
    print(result.get_type())


