#!/usr/bin/env python
#-*- coding: utf-8 -*-

def pancake_sort(data):
    if len(data) <= 1:
        return data

    for size in range(len(data), 1, -1):
        max_index = max(range(size), key=data.__getitem__)
        if max_index + 1 != size:
            if max_index != 0:
                data[:max_index + 1] = reversed(data[:max_index + 1])
            data[:size] = reversed(data[:size])
    return data

if __name__ == '__main__':
    import random
    data = range(10) + [42, 1337, 9001]
    random.shuffle(data)
    print('Original list: ' + ' '.join([str(d) for d in data]))
    pancake_sort(data)
    print('Sorted list: ' + ' '.join([str(d) for d in data]))
