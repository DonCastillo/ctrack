# C-TRACK
![Team logo](docs/czar.png)
## A text-based issue tracking system developed by Team Czar. 
## Project in CPSC 3720: Introduction to Software Engineering

#### TEAM MEMBERS
1. Castillo, Don
2. Hughson, Billy
3. Ward, Dustin
4. Weasel Fat, Riley

## REQUIRED LIBRARIES/FILES
The program uses the following libraries. Make sure they are installed before the program is run.
* [nlohmann/json] (https://github.com/nlohmann/json)
* [restbed] (https://github.com/Corvusoft/restbed)
* A db.json file, that has all the issue and user records, should be in the root directory

## HOW TO RUN
`make server` to build the server, then `make runServer` to run the server in the background.
`make client` to build the client, then `./czarClient` to run the client interface.


## FEATURES
On the console inteface:
* Create a new issue
* Edit an existing issue
* Delete an existing issue
* View an existing issue:
  * View all
  * View by issue ID
* Create a new user
* View an exisiting user:
  * View all
  * View by user ID

On the web browser
* View an issue
  * View all [http://localhost:1234/issues](http://localhost:1234/issues)
  * View by issue ID [http://localhost:1234/issues/{issue_id}](http://localhost:1234/issues/{issue_id})
  * View by status 
    * [http://localhost:1234/issues?status=new](http://localhost:1234/issues?status=new)
    * [http://localhost:1234/issues?status=assigned](http://localhost:1234/issues?status=assigned)
    * [http://localhost:1234/issues?status=fixed](http://localhost:1234/issues?status=fixed)
    * [http://localhost:1234/issues?status=wontfix](http://localhost:1234/issues?status=wontfix)
  * View by type
    * [http://localhost:1234/issues?type=feature](http://localhost:1234/issues?type=feature)
    * [http://localhost:1234/issues?type=bug](http://localhost:1234/issues?type=bug)
    * [http://localhost:1234/issues?type=task](http://localhost:1234/issues?type=task)
  * View by ID range
    * [http://localhost:1234/issues?start={issue_id}&end={issue_id}](http://localhost:1234/issues?start={issue_id}&end={issue_id})
* View a user
  * View all [http://localhost:1234/users](http://localhost:1234/users)
  * View by user ID [http://localhost:1234/users/{user_id}](http://localhost:1234/users/{user_id})
  * View by group
    * [http://localhost:1234/users?group=developer](http://localhost:1234/users?group=developer)
    * [http://localhost:1234/users?group=tester](http://localhost:1234/users?group=tester)
    * [http://localhost:1234/users?group=manager](http://localhost:1234/users?group=manager)
    * [http://localhost:1234/users?group=user](http://localhost:1234/users?group=user)

## KNOWN BUGS
There is an occasional error (error 500: internal server error) when trying to add or update an issue record. To fix this, just try adding/updating a record again or restart the server

## NOT IMPLEMENTED
* User deletion


