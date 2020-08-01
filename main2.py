#!/usr/bin/python
import employeemodule

print("Setting up database")
if employeemodule.cleardb():
    employeemodule.setupdb()

while 1:
    print("C/Python interface.\n")
    print("1. Add\n")
    print("2. Search\n")
    print("3. Delete\n")
    print("4. Modify\n")
    print("5. Reports\n")
    print("6. Exit\n")
    print("Enter your choice: \n")
    try:
        choice = int(input())
        if choice == 1:
            print("Employee Name:")
            name = str(input())
            print("Employee Surname:")
            surname = str(input())
            print("Department:")
            dept = str(input())
            print("Salary:")
            salary = str(input())
            print("Designation:")
            desig = str(input())
            print("Date of Birth")
            dob = str(input())
            print("Employee Type:")
            et = str(input())
            if et not in ['permanent', 'contractual']:
                print("Employee type invalid, try again")
                continue
            if name == '':
                name = 'NULL'
            if surname == '':
                surname = 'NULL'
            if dept == '':
                dept = 'NULL'
            if not salary.isnumeric() or salary == '':
                salary = '0'
            if desig == '':
                desig = 'NULL'
            if dob == '':
                dob = 'NULL'

            if employeemodule.add(name, surname, dept, salary, desig, dob, et):
                print("added")

        if choice == 2:
            print("Enter the employee id:\n")
            emp_id = str(input())
            if not employeemodule.search(emp_id):
                print("No record in the database\n")
            else:
                result = employeemodule.search(emp_id)
                print("Employee id: " + str(result[0]))
                print("Employee First Name: " + str(result[1]))
                print("Employee Last Name: " + str(result[2]))
                print("Employee Department: " + str(result[3]))
                print("Employee Salary: " + str(result[4]))
                print("Employee Designation: " + str(result[5]))
                print("Employee Date of Birth: " + str(result[6]))
                print("Employee Type: " + str(result[7]))

        if choice == 3:
            print("Enter the employee id:\n")
            emp_id = str(input())
            print("Hello")
            # result = employeemodule.delete_emp(emp_id)
            print("hello1")
            result = employeemodule.search(emp_id)
            if not result:
                print("Employee not found")
            else:
                e_id = result[0]
                fn = result[1]
                ln = result[2]
                dn = result[3]
                sal = result[4]
                desig = result[5]
                dob = result[6]
                et = result[7]
                employeemodule.delete_emp(e_id, fn, ln, dn, sal, desig, dob, et)

        if choice == 4:
            print("Enter the employee id:\n")
            emp_id = str(input())
            if not employeemodule.search(emp_id):
                print("No record in the database")
            else:
                result = employeemodule.search(emp_id)
                if not result[1] == "":
                    print("Enter the new first name\n")
                    fn = str(input())
                if not result[2] == "":
                    print("Enter the new last name\n")
                    ln = str(input())
                if not result[3] == "":
                    print("Enter the new department\n")
                    dn = str(input())
                if not result[4] == "":
                    print("Enter the new salary\n")
                    sal = str(input())
                if not result[5] == "":
                    print("Enter the new designation\n")
                    desig = str(input())
                if not result[6] == "":
                    print("Enter the new dob\n")
                    dob = str(input())
                if not result[7] == "":
                    print("Enter the new employee type\n")
                    et = str(input())
                    if et not in ['contractual', 'permanent']:
                        print("Employee type invalid, try again")
                        continue
                modified = employeemodule.modify(emp_id,
                                      fn,
                                      ln,
                                      dn,
                                      sal,
                                      desig,
                                      dob,
                                      et)
                if modified:
                    print("Modified!")
                else:
                    print("Some error occured, try again")

        if choice == 5:
            print("1. List of all employees")
            print("2. Employees for respective department")
            print("3. Total salary for respective department")
            print("4. List permanent/ contractual employees")
            print("Enter your choice:")
            sub_choice = int(input())
            if sub_choice == 1:
                result = employeemodule.report()
                print("Employee ID\tFirst Name\tLast Name\t Department\t Salary\t Designation\t Date of Birth\t Employee Type".expandtabs(10))
                for emp_data in result:
                    print(str(emp_data[0] + '\t' + emp_data[1] + '\t' +
                          emp_data[2] + '\t' + emp_data[3] + '\t' +
                          emp_data[4] + '\t' + emp_data[5] + '\t' +
                          emp_data[6] + '\t' + emp_data[7] + '\t'
                          ).expandtabs(10))
            if sub_choice == 2:
                dept_names = []
                result = employeemodule.report()
                for emp_data in result:
                    if emp_data[3] not in dept_names:
                        dept_names.append(emp_data[3])

                for dept_name in dept_names:
                    print("Department:" + str(dept_name))
                    for emp_data in result:
                        if emp_data[3] == dept_name:
                            print("First Name: " + emp_data[1] + "Last Name: " + emp_data[2])

            if sub_choice == 3:
                dept_names = []
                result = employeemodule.report()
                for emp_data in result:
                    if emp_data[3] not in dept_names:
                        dept_names.append(emp_data[3])

                for dept_name in dept_names:
                    print("Department:" + str(dept_name))
                    salary = 0
                    for emp_data in result:
                        if emp_data[3] == dept_name:
                            if emp_data[7] == "permanent":
                                salary += (int(emp_data[4]) +
                                           0.1 * int(emp_data[4]) +
                                           0.15 * (int(emp_data[4])) +
                                           0.12 * int(emp_data[4]) -
                                           0.1 * int(emp_data[4]))
                            else:
                                salary += (int(emp_data[4]) +
                                           0.1 * int(emp_data[4]) +
                                           0.15 * (int(emp_data[4])) -
                                           0.1 * int(emp_data[4]))
                    salary = round(salary, 2)
                    print("Total Salary: " + str(salary))

            if sub_choice == 4:
                employee_type = ['permanent', 'contractual']
                result = employeemodule.report()
                for et in employee_type:
                    print("Employee type: " + et)
                    for emp_data in result:
                        if emp_data[7] == et:
                            print("First Name: " + emp_data[1] + " Last Name:" + emp_data[2])

        if choice == 6:
            employeemodule.cleardb()
            break
    except Exception as e:
        print(e)
        continue

