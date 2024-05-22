from sys import argv as av
from ai.src.arguments import parse_args

args = parse_args(av[1:])

print(args)
