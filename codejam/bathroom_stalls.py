#!/usr/bin/env python3

import queue

def f(N, K):
    queue_ = queue.PriorityQueue()
    map_ = {}
    count = 0

    queue_.put(-N)
    map_[N] = 1

    while not queue_.empty():
        size = -queue_.get()
        left_size = (size - 1) // 2
        right_size = size // 2

        if count + map_[size] >= K:
            return (right_size, left_size)

        count += map_[size]

        if left_size not in map_:
            map_[left_size] = 0
            queue_.put(-left_size)

        if right_size not in map_:
            map_[right_size] = 0
            queue_.put(-right_size)

        map_[left_size] += map_[size]
        map_[right_size] += map_[size]

    return (-1, -1)


if __name__ == '__main__':
    number_of_tests = int(input())

    for i in range(number_of_tests):
        line = input().split(' ')
        N, k = int(line[0]), int(line[1])
        r = f(N, k)

        print('Case #{case}: {max} {min}'.format(case=i+1, max=r[0], min=r[1]))

