Database updates
================
This folder contains SQL files which will apply required updates to your MySQL
database, whenever the MaNGOS database structure has been changed or extended.

To see if you need an update, the file names have been given a fixed structure
that should enable you to see if you need an update or not.

Filename description
--------------------
Filenames are divided into two parts:

* first part is the order_number, revision and counter that shows the commit
  revision that is compatible with the database after apply that particular update.
  Counter sets the order to apply SQL updates for the same revision. Order_number
  sets global order in directory for back-ported SQL updates (it's back-ported in
  random order and need special mangos-zero side order to apply)
* the second part of the name is the database and the table that needs an update
  or has been added.

Example
-------
    z0001_xxx_01_characters_character_db_version.sql
    |     |   |  |          |
    |     |   |  |          |
    |     |   |  |          The table `character_db_version`
    |     |   |  |          will need an update.
    |     |   |  |
    |     |   |  Name of affected DB (default recommended name)
    |     |   |  Can be: characters, mangos, realmd
    |     |   |
    |     |   Counter show number of SQL update in 0.12 back-ported or own (non back-ported, xxx) updates list for provided master revision
    |     |   and set proper order for SQL updates for same revision
    |     |
    |     MaNGOS 0.12 commit revision related to SQL update (if this back-ported SQL update.
    |     It can be absent (and replaced by xxx) if SQL update not really back-ported but only mangoszero specific.
    |
    Order_number set special order for apply SQL updates from different back-ported revisions in mangoszero

After applying an update, the database is compatible with the *mangos-zero* revision
of this update. Updates include special protection against multiple and wrong order
of update usage.

Attempts to apply updates to an older database without previous updates will generate
an error and not be applied.

Creating updates
----------------
*Notice*: you have to use the `git_id` tool from the contributed sources.

* Name the update in *mangos-zero* form: `z9999_xxxxxx_01_database_table.sql`
* Add the update to commit and manually include SQL update changes in the related
  database file.
* Now use `git_id -s`. The update revision will updates in name, guards will added
  to the update, required revision data will be updated in related database file
  and in `src/shared/revision_sql.h`.
