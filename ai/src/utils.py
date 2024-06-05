def clean_str(str: str) -> str:
    str = str.replace("[", "")
    str = str.replace(" ", "", 1)
    str = str.replace("]", "")
    str = str.replace("\n", "")
    return str

def print_verbose(verbose: bool, str) -> None:
    if verbose:
        print(f"{str}", end="")
