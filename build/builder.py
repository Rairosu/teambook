from pathlib import Path


def write_algos(fd):
    for d in Path("../").iterdir():
        if d.is_dir() and d.name not in [".git", "build"]:
            fd.write(f"\\subsection{{{d.name.replace('_', ' ')}}}\n".encode())
            for f in d.iterdir():
                fd.write(
                    f"\\subsubsection{{{f.name[:-4].replace('_', ' ')}}}\n".encode()
                )
                fd.write(
                    f"""\\begin{{lstlisting}}\n{f.read_text()}\\end{{lstlisting}}\n""".encode()
                )


def main():
    with open("src/algorithms.tex", "wb") as fd:
        fd.write(b"\\section{Algorithms}\n\n")
        write_algos(fd)


if __name__ == "__main__":
    main()
