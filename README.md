# PasswordManager
A small educational project created while studying at the university.
Written using C++ in the Qt Creator with Qt 6.2.2.Sqlite is used as a database.
This is an unfinished project that does not guarantee full functionality and protection of personal information.

## Usage
The user has access to such functions as:
* Creating a database
* Opening an existing database
* Exporting the current database
* Creating/reading/modifying entries
* Search for entries

When creating a database, the user enters a password, which is subsequently used as an encryption key to the records. 
AES 128 with ECB mode is used for encryption using a third-party class [Qt-AES](https://github.com/bricke/Qt-AES).
The information is encrypted and recorded in a local database. When reading records, the information is decrypted and output to the user interface.
The user cannot change the password. If user opens the database with an incorrect password, the information will not be decrypted.

## Ideas for future development

* Changing the type of database
* Usage of AES-256 instead of AES-128
* Encrypt full database instead of entries
