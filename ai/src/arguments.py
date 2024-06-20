from argparse import ArgumentParser, ArgumentTypeError

def parse_args(av):
    parser = ArgumentParser(description="./zappy_ai -p port -n name -h machine", add_help=False)
    parser.add_argument("-p", type=int, help="port number")
    parser.add_argument("-n", type=str, help="name of the team")
    parser.add_argument("-h", type=str, help="name of the machine; localhost by default", default="localhost")
    parser.add_argument("--verbose", action="store_true", dest="verbose", help="Show debug log", default=False)
    parser.add_argument('-help', action='help')

    if len(av) == 0:
        print("ERROR: no arguments")
        exit(84)

    try:
        args = parser.parse_args(av)
    except SystemExit:
        exit(84)

    return args
