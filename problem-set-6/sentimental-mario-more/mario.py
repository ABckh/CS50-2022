def main():
    height = get_height()
    for i in range(1, height + 1):
        spaces = ' ' * (height - i)
        blocks = "#" * i
        print(f"{spaces}{blocks} {blocks}{spaces}")


def get_height():
    while True:
        try:
            height = int(input("Height: "))
            if 0 < height <= 8:
                return height
            else:
                print("Height must be bigger than 0 and less than 9")
        except ValueError:
            print("Height must be a number")


if __name__ == "__main__":
    main()