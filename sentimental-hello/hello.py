def main():
    print(getName())
def getName():
    name=str(input("What is your Name? "))
    return ("hello "+name)
if __name__ == "__main__":
    main()