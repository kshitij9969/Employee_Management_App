from distutils.core import setup, Extension

def main():
    setup(name="employeemodule",
          version="1.0.0",
          description="Python interface for the fputs C library function",
          author="<your name>",
          author_email="your_email@gmail.com",
          ext_modules=[Extension("employeemodule", ["employeemodule.cpp"])])

if __name__ == "__main__":
    main()