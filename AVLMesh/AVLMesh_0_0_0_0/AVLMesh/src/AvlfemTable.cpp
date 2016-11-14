#include "AvlfemTable.h"

AvlfemTable::AvlfemTable(AvlfemTable01TableTypeI4 avlfem_table_01_type_param_i4,
                      string avlfem_table_01_element_definition_param_c1,
                      int avlfem_table_01_nb_element_param_i4)
{
  /* Input - Constructor
  Initializing the value of all the explicit parameters.
  */
  avlfem_table_01_element_definition_c1 = avlfem_table_01_element_definition_param_c1;
  avlfem_table_01_nb_element_i4 = avlfem_table_01_nb_element_param_i4;

  /* Process - Constructor
  Decode the definition string to define the non-explicit parameters.
  */
  AvlfemTable01DecodeElementDefinition00();
}

AvlfemTable::~AvlfemTable()
{
  //dtor
}

/** Decode Element's Definition
    This function will decode the element's definition string. */
void AvlfemTable::AvlfemTable01DecodeElementDefinition00()
{
  /* Declaration - AvlfemTable01DecodeElementDefinition00
  Initializing all the variables used in the function.
  */
  // String iteration counter
  unsigned int i = 0;

  // Variable iteration counter
  unsigned int j = 0;

  // State boolean to define if a name or a type will be decoded
  bool is_name = true;

  // Count the number of variable
  unsigned int variable_count = 0;

  // Temporary string to old the type
  string variable_type_temporary = "";

  // Temporary size of the type
  int variable_size_temporary = 0;

  // Initialize the size of an element
  avlfem_table_01_element_size_i4 = 0;


  /* Process - AvlfemTable01DecodeElementDefinition00
  Decode the string to find the name of the element section and it's type.
  */
  for(;i <= avlfem_table_01_element_definition_c1.length(); ++i)
  {
    /* Define the state of the states machine */
    if (avlfem_table_01_element_definition_c1[i] == ' ' || i == avlfem_table_01_element_definition_c1.length())
    {
      // When a space is encountered, the state changes from name to type, or vice-versa.
      is_name = !is_name;
      // We also don't want to decode the ' ' character
      i++;

      // If we start a new name, then it means that the type is ready to be defined and a new variable is starting, thus we increment the variable count.
      if(is_name)
      {
        avlfem_table_01_variable_types_i4[variable_count] = AvlfemTable01DecodeTypeI4(variable_type_temporary);
        // Increment the size of one element by the size of the variable.
        switch(avlfem_table_01_variable_types_i4[variable_count])
        {
          case AvlfemTable::F8:
            variable_size_temporary = sizeof(double);
            break;
          case AvlfemTable::F4:
            variable_size_temporary = sizeof(float);
            break;
          case AvlfemTable::I4:
            variable_size_temporary = sizeof(int);
            break;
          case AvlfemTable::C1:
            variable_size_temporary = sizeof(char);
            break;
          case AvlfemTable::L1:
            variable_size_temporary = sizeof(bool);
            break;
          default:
            variable_size_temporary = 0;
        }
        avlfem_table_01_variable_size_i4[variable_count] = variable_size_temporary;
        avlfem_table_01_element_size_i4 += variable_size_temporary;
        // Don't forget to clear the temporary string for the next variable.
        variable_type_temporary = "";
        variable_count++;
      }
    }
    /* States machine to decode the name and type */
    // Decode a name
    if(i <= avlfem_table_01_element_definition_c1.length())
    {
      if (is_name)
      {
        avlfem_table_01_variable_names_c1[variable_count] += avlfem_table_01_element_definition_c1[i];
      }
      // Decode a type
      else
      {
        variable_type_temporary += avlfem_table_01_element_definition_c1[i];
      }
    }
  }

  /* Output - AvlfemTable01DecodeElementDefinition00
  Output a log on the command prompt detailing what was decoded
  */
  cout << "[INFO] Table decoded with success : " << endl;
  cout << "[INFO] Each element of the table is " << avlfem_table_01_element_size_i4 << " bytes." << endl;
  cout << "| Id | Variable Name | Variable Type | Size |" << endl;
  for(; j < variable_count; ++j)
  {
    switch(avlfem_table_01_variable_types_i4[j])
        {
          case AvlfemTable::F8:
            variable_type_temporary = "F8";
            break;
          case AvlfemTable::F4:
            variable_type_temporary = "F4";
            break;
          case AvlfemTable::I4:
            variable_type_temporary = "I4";
            break;
          case AvlfemTable::C1:
            variable_type_temporary = "C1";
            break;
          case AvlfemTable::L1:
            variable_type_temporary = "L1";
            break;
          default:
            variable_type_temporary = "";
        }
    cout << "| " << j << "  | " << avlfem_table_01_variable_names_c1[j];
    for(i = 0; i < 13 - avlfem_table_01_variable_names_c1[j].length(); ++i)
    {
      cout << " ";
    }
    cout << " | " << variable_type_temporary << "            | " << avlfem_table_01_variable_size_i4[j] << "    |" << endl;
  }
}

/** Associate a string to enumeration
    This function will associate a string type to its associated enumeration. */
AvlfemTable::AvlfemTable01VariableTypeI4 AvlfemTable::AvlfemTable01DecodeTypeI4(string avlfem_table_01_variable_type_param_c1)
{
  /* Input - AvlfemTable01DecodeTypeI4
  Initialize the output variable.
  */
  AvlfemTable::AvlfemTable01VariableTypeI4 output_type;

  /* Process - AvlfemTable01DecodeTypeI4
  Do the association between the string and the enumeration
  */
  if (avlfem_table_01_variable_type_param_c1 == "F8")
  {
    output_type = AvlfemTable::F8;
  }
  else if (avlfem_table_01_variable_type_param_c1 == "F4")
  {
    output_type = AvlfemTable::F4;
  }
  else if (avlfem_table_01_variable_type_param_c1 == "I4")
  {
    output_type = AvlfemTable::I4;
  }
  else if (avlfem_table_01_variable_type_param_c1 == "C1")
  {
    output_type = AvlfemTable::C1;
  }
  else if(avlfem_table_01_variable_type_param_c1 == "L1")
  {
    output_type = AvlfemTable::L1;
  }
  else
  {
    throw new InvalidVariableTypeException();
  }

  /* Output - AvlfemTable01DecodeTypeI4
  Return the output variable.
  */

  return output_type;
}
