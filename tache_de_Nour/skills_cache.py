import sqlite3
import hashlib
import os

DB_PATH = os.path.join(os.path.dirname(__file__), "skills_cache.db")

def get_cv_hash(file_path):
    with open(file_path, "rb") as f:
        return hashlib.md5(f.read()).hexdigest()

def get_cached_skills(cv_hash):
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    cursor.execute("CREATE TABLE IF NOT EXISTS cached_skills (cv_hash TEXT PRIMARY KEY, skills TEXT)")
    cursor.execute("SELECT skills FROM cached_skills WHERE cv_hash = ?", (cv_hash,))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else None

def cache_skills(cv_hash, skills):
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    cursor.execute("INSERT OR REPLACE INTO cached_skills (cv_hash, skills) VALUES (?, ?)", (cv_hash, skills))
    conn.commit()
    conn.close()
