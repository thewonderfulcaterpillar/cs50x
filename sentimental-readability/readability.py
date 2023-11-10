strLen = 0

def count_letters(text):
    letterCount = 0
    for i in range(strLen):
        c = ord(text[i].lower()) - ord('a')
        if 0 <= c < 26:
            letterCount += 1
    return letterCount

def count_words(text):
    wordCount = 1
    for i in range(strLen):
        if text[i] == ' ':
            wordCount += 1
    return wordCount

def count_sentences(text):
    sentenceCount = 0
    for i in range(strLen):
        if text[i] in ['!', '.', '?']:
            sentenceCount += 1
    return sentenceCount

def main():
    global strLen
    x = input("Please input a string for the readability test: ")
    strLen = len(x)
    letters = count_letters(x)
    words = count_words(x)
    sentences = count_sentences(x)
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        grade = round(index)
        print(f"Grade {grade}")

if __name__ == "__main__":
    main()
