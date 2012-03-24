#!/usr/bin/env python
#-*- coding: utf-8 -*-

from itertools import product
from functools import lru_cache

class MastermindSolver(object):
    def __init__(self, problem_set):
        self.problem_set = problem_set
        self.possible_solutions = [''.join(s) for s in product(self.problem_set, repeat=4)]
        self.results = [(correct, incorrect)
                for correct in range(5)
                for incorrect in range(5 - correct)
                if not (correct == 3 and incorrect == 1)]

    def solve(self, solution):
        return self._solve(set(self.possible_solutions), solution, (), [])

    def _solve(self, possible_solutions, solution, score, steps, attempts=1):
        if attempts == 1:
            # first through, get AABB
            attempt = 'AABB'
        elif attempts == 2 and score[0] == 0:
            # second time through, first score for 'AABB' returned 0
            attempt = 'CCDE'
        elif len(possible_solutions) == 1:
            attempt = possible_solutions.pop()
        else:
            attempt = max(self.possible_solutions, key=lambda x:
                    min(sum(1 for p in possible_solutions if self._score(p, x) != r)
                        for r in self.results))

        score = self._score(solution, attempt)

        steps.append((attempts, attempt, score))

        if score != (4, 0):
            possible_solutions.difference_update(set(p for p in possible_solutions
                if self._score(p, attempt) != score))
            return self._solve(possible_solutions, solution, score, steps, attempts + 1)

        return steps

    @lru_cache(maxsize=None)
    def _score(self, sol, attempts):
        first = len([speg for speg, opeg in zip(sol, attempts) if speg == opeg])
        score = sum([min(sol.count(c), attempts.count(c)) for c in self.problem_set]) - first
        return first, score

def format_steps(steps):
    for step in steps:
        print("%d. %s %s%s" % (step[0], step[1], step[2][0] * "+", step[2][1] * "-"))

def main():
    import sys
    solution = len(sys.argv) > 1 and sys.argv[1] or raw_input("Enter a solution: ")
    solver = MastermindSolver('ABCDEF')
    print("Attempting to solve " + solution)
    steps = solver.solve(solution)
    format_steps(steps)
    print("Solved in %d steps!" % len(steps))

if __name__ == '__main__':
    main()
