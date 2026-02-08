static const char *tables =
"CREATE TABLE IF NOT EXISTS Admins ("
"    id INTEGER PRIMARY KEY AUTOINCREMENT,"
"    username TEXT NOT NULL UNIQUE,"
"    password TEXT NOT NULL"
");"

"CREATE TABLE IF NOT EXISTS Students ("
"    id INTEGER PRIMARY KEY AUTOINCREMENT,"
"    username TEXT NOT NULL UNIQUE,"
"    password TEXT NOT NULL"
");"

"CREATE TABLE IF NOT EXISTS Exams ("
"    id INTEGER PRIMARY KEY AUTOINCREMENT,"
"    title TEXT UNIQUE,"
"    duration INTEGER,"
"    questions TEXT NOT NULL"
");"

"CREATE TABLE IF NOT EXISTS Results ("
"    id INTEGER PRIMARY KEY AUTOINCREMENT,"
"    student_id INTEGER NOT NULL,"
"    exam_id INTEGER NOT NULL,"
"    grade REAL NOT NULL,"

"    FOREIGN KEY (exam_id) REFERENCES Exams(id) ON DELETE CASCADE"
"    FOREIGN KEY (student_id) REFERENCES Students(id) ON CASCADE"
");"
;
