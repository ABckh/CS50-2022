def main() -> None:
    text = input("Text: ")
    grade = get_index(text)
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade: {grade}")


def get_index(text: str) -> int:
    letters = get_letters_number(text)
    words = get_words_number(text)
    sentences = get_sentences_number(text)

    average_letters = 100.0 * letters / words
    average_sentences = 100.0 * sentences / words
    index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8
    return round(index)

    
def get_letters_number(text: str) -> float:
    counter = 0
    for char in text:
        if char.isalpha():
            counter += 1
    return counter


def get_words_number(text: str) -> float:
    counter = 0
    for char in text:
        if char.isspace():
            counter += 1
    return counter + 1


def get_sentences_number(text: str) -> float:
    counter = 0
    for char in text:
        if char == '.' or char == '!' or char == '?':
            counter += 1
    return counter


if __name__ == "__main__":
    main()