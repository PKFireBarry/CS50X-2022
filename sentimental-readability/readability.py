from cs50 import get_string

#getting the words to check for grade_level
string = get_string(": ")

#setting the counts for the words, letters, sentences
letters = 0
words = 0
sentences = 0

#search for words, letters, sentences
for i in range(len(string)):
    if string[i].isalpha():
        letters += 1
    if string[i] == ' ':
        words += 1
    if string[i] == '!' or string[i] == '.' or string[i] == '?':
        sentences += 1

#adding the last word
words += 1

L = letters/ words * 100
S = sentences / words * 100

#foluala for grade level
CLI = (0.0588 * L) - (0.296 * S) - 15.8
grade_level = round(CLI)

#printing the grade level
if grade_level < 1:
    print("Before Grade 1")
elif grade_level >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade_level}")
