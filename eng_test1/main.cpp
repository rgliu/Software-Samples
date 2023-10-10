#include <iostream>

#include "testlib.h"

/*
    Richard Liu
 
    CreateProc: Creates TheProc object and returns a unique ID associated to the provided Proc name
                    - ID is of type std::size_t because that is what hash the function returns AND is all positive

                Attempting to create a second TheProc object with a name that already exists will result in no-op
                    - To overwrite, first Proc object of that name must be destroyed first (DestroyProc)
 
                Since we do not know how many Procs to expect, std::map is the better choice to store
                    - more space efficient than std::unordered_map while still having quick lookup
 
    RunProc: Run ProcID 
 
    GetProcName: Print name associated to given ID
 
    DestroyProc: Delete Proc associated to ID
 */

int main(int, char**) {
    {
        // Example of creating an instance of the Proc and running it
        std::cout << "TC1\n";
        std::size_t proc_id = CreateProc("Proc1", "Keyword", "Region Name");
        RunProc(proc_id, 10);
        DestroyProc(proc_id);
        std::cout << "\n";
    }

    {
        // Make the proc ID field functional so multiple Procs can be created and destroyed
        std::cout << "TC2\n";
        std::size_t proc_id_one = CreateProc("Proc1", "Keyword", "Region Name");
        std::size_t proc_id_two = CreateProc("Proc2", "OtherKey", "Region Name");
        std::cout << "\n";

        RunProc(proc_id_one, 15);
        RunProc(proc_id_two, 20);
        std::cout << "\n";

        GetProcName(proc_id_one);
        GetProcName(proc_id_two);
        std::cout << "\n";

        DestroyProc(proc_id_one);
        DestroyProc(proc_id_two);
        std::cout << "\n";
    }


    {
        // Add a 'name' field to the proc library for instances and print it out
        std::cout << "TC3\n";
        std::size_t proc_id_one = CreateProc("FirstProc", "Keyword", "Region Name");
        std::size_t proc_id_two = CreateProc("SecondProc", "OtherKey", "Region Name");
        std::cout << "\n";

        GetProcName(proc_id_one);
        GetProcName(proc_id_two);
        std::cout << "\n";

        DestroyProc(proc_id_two); // release second one first
        DestroyProc(proc_id_one);
        std::cout << "\n";
    }

    {
        // Some test cases

        // proc_id_one and proc_id_two refer to the same Proc Object (proc_id_one's)
        std::cout << "TC4\n";
        std::size_t proc_id_one = CreateProc("FirstProc", "ThisOne", "Region Name");
        std::size_t proc_id_two = CreateProc("FirstProc", "NotThisOne", "Region Name"); // returns same ID as proc_id_one
        std::cout << "\n";

        GetProcName(proc_id_one);
        GetProcName(proc_id_two); // Returns proc_id_one's PROC
        std::cout << "\n";

        DestroyProc(proc_id_one);
        DestroyProc(proc_id_two); // Will print "ERROR PROC_ID not found!"
        std::cout << "\n";

        GetProcName(proc_id_one); // Will print "ERROR PROC_ID not found!"
        std::cout << "\n";
    }

    return 0;
}
