# extract_skills.py
import sys
from PyPDF2 import PdfReader
from skills_cache import get_cv_hash, get_cached_skills, cache_skills

from extract_logic import extract_skills_from_pdf

SKILLS = {"python", "c++", "java", "sql", "machine learning", "react", "node.js", "ai", "deep learning"}

def extract_text_from_pdf(pdf_path):
    text = ""
    try:
        reader = PdfReader(pdf_path)
        for page in reader.pages:
            text += page.extract_text() or ""
    except Exception as e:
        print(f"ERROR: {e}")
    return text.lower()

def extract_skills(text):
    found_skills = set()
    for skill in SKILLS:
        if skill.lower() in text:
            found_skills.add(skill)
    return list(found_skills)
def main():
    if len(sys.argv) != 2:
        print("Usage: extract_skills.py <pdf_path>")
        return

    pdf_path = sys.argv[1]
    cv_hash = get_cv_hash(pdf_path)

    cached = get_cached_skills(cv_hash)
    if cached:
        print(cached)
        return

    # If not cached, extract
    skills = extract_skills_from_pdf(pdf_path)
    result = ", ".join(skills)

    # Save to cache
    cache_skills(cv_hash, result)

    print(result)

if __name__ == "__main__":
    main()

