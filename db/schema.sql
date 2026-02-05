-- ======================================================
-- CBES Database Schema
-- ======================================================

-- Admin credentials for authentication
CREATE TABLE IF NOT EXISTS Admins (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS Students (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
);

-- Exam data storage (supports JSON format for questions)
CREATE TABLE IF NOT EXISTS Exams (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT,
    questions TEXT NOT NULL,
);

-- Students exam results and scores
CREATE TABLE IF NOT EXISTS Results (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    student_id INTEGER NOT NULL,
    exam_id INTEGER NOT NULL,
    grade REAL NOT NULL,

    -- Relationship: Links result to a specific exam
    FOREIGN KEY (exam_id) REFERENCES Exams(id) ON DELETE CASCADE
);
