-- ======================================================
-- CBES Database Schema
-- ======================================================

-- Admin credentials for authentication
CREATE TABLE IF NOT EXISTS Admins (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
);

-- Exam data storage (supports JSON format for questions)
CREATE TABLE IF NOT EXISTS Exams (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    questions_json TEXT, 
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Students exam results and scores
CREATE TABLE IF NOT EXISTS Results (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    student_name TEXT NOT NULL,
    exam_id INTEGER,
    score REAL NOT NULL,
    total_questions INTEGER,
    exam_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    
    -- Relationship: Links result to a specific exam
    FOREIGN KEY (exam_id) REFERENCES Exams(id) ON DELETE CASCADE
);