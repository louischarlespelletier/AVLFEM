#ifndef AVLFEMCOORDTABLE_H
#define AVLFEMCOORDTABLE_H

#include <iostream>
#include <exception>
#include <string>

using namespace std;

class InvalidVariableTypeException: public exception
{
  virtual const char* what() const throw()
  {
    return "The selected type defined in the AvlfemTable element definition is not a valid type. Supported types are the following : F4, I4, C1 and L1.";
  }
};

/** Base Table Element :
This class is in charge of handling the data composing it. The user will be able to create it, add/remove/view/edit elements and destroy it.

The table will be created in the following manner :

| element #1 byte #1 | element #1 byte #2 |
| element #2 byte #1 | element #2 byte #2 |
| ...                      | ...                      |

*/

class AvlfemTable
{
  public:

    /** AvlfemTable01TableTypeI4
    Static : Standard static array loaded in the RAM
      Pros
        Defined space in memory
        Fast to go to a specific ID
      Cons
        Slow to remove or insert an existing element
        Number of elements must be predefined
    DynamicLinked : Linked array where each entry gives a link to its next and previous element.
      Pros
        Faster to insert or remove elements in the middle of the array
      Cons
        Slow to get to a specific ID
    */
    enum AvlfemTable01TableTypeI4 {Static, DynamicLinked};

    enum AvlfemTable01VariableTypeI4 {F8, F4, I4, C1, L1};

    // Functions

    /** Type constructor */
    AvlfemTable(AvlfemTable01TableTypeI4 avlfem_table_01_type_param_i4,
                      string avlfem_table_01_element_definition_param_c1,
                      int avlfem_table_01_nb_element_param_i4);

    /** Default destructor */
    virtual ~AvlfemTable();

    // Variables

    // Constants

    /** Maximum number of variable in one element */
    static const unsigned int avlfem_table_01_max_element_name_i4 = 12;

  private:

    // Functions

    /** Decode Element's Definition.
    This function will decode the element's definition string. */
    void AvlfemTable01DecodeElementDefinition00();

    AvlfemTable01VariableTypeI4 AvlfemTable01DecodeTypeI4(string avlfem_table_01_variable_type_param_c1);

    // Variables

    /** Table type definition.
    It will serve to define how the table elements are handled by the system. */
    AvlfemTable01TableTypeI4 avlfem_table_01_type_i4;

    /** Definition of an element in a raw string. This will be decoded and will
    be used to build each element of the table. */
    /* This string is must be formatted as follow: "ElementName Type ElementName Type"
       Where the type can be either F4, I4, C1 or L1*/
    string avlfem_table_01_element_definition_c1;

    /** Array of the names of the variables of one element */
    string avlfem_table_01_variable_names_c1[avlfem_table_01_max_element_name_i4];

    /** Array of the types of the variables of one element */
    AvlfemTable01VariableTypeI4 avlfem_table_01_variable_types_i4[avlfem_table_01_max_element_name_i4];

    /** Array of the size of the variables of one element */
    int avlfem_table_01_variable_size_i4[avlfem_table_01_max_element_name_i4];

    /** Maximum element number */
    int avlfem_table_01_nb_element_i4;

    /** Size of one element */
    int avlfem_table_01_element_size_i4;
};

#endif // AVLFEMCOORDTABLE_H
