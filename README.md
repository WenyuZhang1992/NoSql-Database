# NoSql-Database

## Enviroment:
* Visual Studio 2015
* Language: C++

## Description: This project creates a NoSql database using C++.
* Inside the database, each entry is a **key-value** pair.
* Support all databse operations: **insert, delete, edit, query(intersection, union) and persist**
* Support restore from and save to xml files
* Auto-save to xml file after certain updates

### Entry Structure:
* Key: string type
* Metadata: data used to describe value, including: item name, category name, add time, **child collection(collections of keys)**, description
* Value: template-type value
