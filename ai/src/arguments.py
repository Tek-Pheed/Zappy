from argparse import ArgumentParser, ArgumentTypeError

def parse_args(av):
    parser = ArgumentParser(description="./zappy_ai -p port -n name -h machine", add_help=False)
    parser.add_argument("-p", type=int, help="port")
    parser.add_argument("-n", type=str, help="name")
    parser.add_argument("-h", type=str, help="machine")
    parser.add_argument('-help', action='help')

    try:
        args = parser.parse_args(av)
    except SystemExit:
        exit(84)

    return args