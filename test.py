data = [("p", 1), ("p", 2), ("p", 3),
        ("h", 1), ("h", 2), ("h", 3)]
result = {}
for (key, value) in data:
    if key in result:
        result[key].append(value)
    else:
        result[key] = [value]
print(result)