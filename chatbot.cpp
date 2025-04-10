#include "chatbot.h"
#include <QDebug>
#include <QSqlError>
#include <QRandomGenerator>
#include <QDateTime>

ChatBot::ChatBot(QObject *parent) : QObject(parent)
{
    initializeKnowledgeBase();
}

ChatBot::~ChatBot()
{
}

QString ChatBot::processInput(const QString &input)
{
    // Normalize input: trim and convert to lowercase
    QString normalizedInput = input.trimmed().toLower();

    // Recognize intent
    Intent intent = recognizeIntent(normalizedInput);

    // Generate response based on intent
    return generateResponse(intent, normalizedInput);
}

void ChatBot::initializeKnowledgeBase()
{
    // Initialize greetings
    greetings << "Hello! How can I help you with sponsor information?"
              << "Hi there! I can answer questions about our sponsors."
              << "Welcome! Looking for sponsor information?"
              << "Greetings! How may I assist you with sponsors today?";

    // Initialize farewells
    farewells << "Goodbye! Feel free to ask about sponsors anytime."
              << "See you later! Let me know if you need more information."
              << "Bye! Have a great day!"
              << "Until next time! Don't hesitate to reach out for sponsor info.";

    // Initialize unknown responses
    unknownResponses << "I'm not sure I understand. Could you rephrase your question about sponsors?"
                     << "I didn't catch that. Try asking about specific sponsors or domains."
                     << "Sorry, I don't have information about that. I can help with sponsor details though."
                     << "I'm still learning. Could you ask me something about sponsors in our database?";

    // Initialize domain keywords
    domainKeywords["Technology"] = QStringList() << "tech" << "technology" << "it" << "software" << "hardware" << "digital";
    domainKeywords["Finance"] = QStringList() << "finance" << "financial" << "banking" << "bank" << "investment";
    domainKeywords["Health"] = QStringList() << "health" << "healthcare" << "medical" << "hospital" << "pharma";
    domainKeywords["Retail & E-commerce"] = QStringList() << "retail" << "e-commerce" << "shop" << "store" << "shopping";
    domainKeywords["Education & Training"] = QStringList() << "education" << "school" << "university" << "training" << "learning";
    domainKeywords["Media & Entertainement"] = QStringList() << "media" << "entertainment" << "film" << "movie" << "tv" << "television";
    domainKeywords["Automotive"] = QStringList() << "automotive" << "car" << "vehicle" << "auto" << "automobile";
    domainKeywords["Food"] = QStringList() << "food" << "restaurant" << "catering" << "cuisine" << "grocery";
    domainKeywords["Real Estate"] = QStringList() << "real estate" << "property" << "housing" << "realty" << "building";
    domainKeywords["Other"] = QStringList() << "other" << "miscellaneous" << "various" << "diverse";

    // Initialize intent patterns
    intentPatterns["GREETING"] = QRegularExpression("\\b(hi|hello|hey|greetings|good morning|good afternoon|good evening)\\b",
                                                    QRegularExpression::CaseInsensitiveOption);

    intentPatterns["FAREWELL"] = QRegularExpression("\\b(bye|goodbye|see you|farewell|exit|quit)\\b",
                                                    QRegularExpression::CaseInsensitiveOption);

    intentPatterns["LIST_SPONSORS"] = QRegularExpression("\\b(list|show|display|all)\\s+(sponsors?|companies?)\\b",
                                                         QRegularExpression::CaseInsensitiveOption);

    intentPatterns["FIND_SPONSOR_BY_NAME"] = QRegularExpression("\\b(find|search|get|tell me about)\\s+(sponsor|company)\\s+(named|called|with name)\\s+([a-zA-Z0-9\\s&]+)\\b",
                                                                QRegularExpression::CaseInsensitiveOption);

    intentPatterns["FIND_SPONSOR_BY_CODE"] = QRegularExpression("\\b(find|search|get|sponsor with|company with)\\s+(code|fiscal code|registration|cr)\\s+([A-Z0-9]+)\\b",
                                                                QRegularExpression::CaseInsensitiveOption);

    intentPatterns["FIND_SPONSORS_BY_DOMAIN"] = QRegularExpression("\\b(sponsors?|companies?)\\s+(in|from|working in|specialized in)\\s+([a-zA-Z\\s&]+)\\b",
                                                                   QRegularExpression::CaseInsensitiveOption);

    intentPatterns["FIND_SPONSORS_BY_CAPACITY"] = QRegularExpression("\\b(sponsors?|companies?)\\s+(with|having)\\s+(capacity|financial capacity|budget|funding)\\s+(between|above|below|over|under)\\s+([0-9.,]+)\\s*(and|to)?\\s*([0-9.,]+)?\\b",
                                                                     QRegularExpression::CaseInsensitiveOption);

    intentPatterns["BEST_SPONSOR"] = QRegularExpression("\\b(best|top|highest|leading|premier)\\s+(sponsor|company|financial capacity)\\b",
                                                        QRegularExpression::CaseInsensitiveOption);

    intentPatterns["GET_CONTACT_INFO"] = QRegularExpression("\\b(contact|email|phone|telephone|address|information)\\s+(for|of|about)\\s+([a-zA-Z0-9\\s&]+)\\b",
                                                            QRegularExpression::CaseInsensitiveOption);
}

ChatBot::Intent ChatBot::recognizeIntent(const QString &input)
{
    // Check for greeting
    if (intentPatterns["GREETING"].match(input).hasMatch()) {
        return GREETING;
    }

    // Check for farewell
    if (intentPatterns["FAREWELL"].match(input).hasMatch()) {
        return FAREWELL;
    }

    // Check for list sponsors
    if (intentPatterns["LIST_SPONSORS"].match(input).hasMatch()) {
        return LIST_SPONSORS;
    }

    // Check for find sponsor by name
    if (intentPatterns["FIND_SPONSOR_BY_NAME"].match(input).hasMatch()) {
        return FIND_SPONSOR_BY_NAME;
    }

    // Check for find sponsor by code
    if (intentPatterns["FIND_SPONSOR_BY_CODE"].match(input).hasMatch()) {
        return FIND_SPONSOR_BY_CODE;
    }

    // Check for find sponsors by domain
    if (intentPatterns["FIND_SPONSORS_BY_DOMAIN"].match(input).hasMatch()) {
        return FIND_SPONSORS_BY_DOMAIN;
    }

    // Check for find sponsors by capacity
    if (intentPatterns["FIND_SPONSORS_BY_CAPACITY"].match(input).hasMatch()) {
        return FIND_SPONSORS_BY_CAPACITY;
    }

    // Check for best sponsor
    if (intentPatterns["BEST_SPONSOR"].match(input).hasMatch()) {
        return BEST_SPONSOR;
    }

    // Check for contact information
    if (intentPatterns["GET_CONTACT_INFO"].match(input).hasMatch()) {
        return GET_CONTACT_INFO;
    }

    // If no match, return unknown
    return UNKNOWN;
}

QString ChatBot::generateResponse(Intent intent, const QString &input)
{
    switch (intent) {
    case GREETING: {
        // Return a random greeting
        int index = QRandomGenerator::global()->bounded(greetings.size());
        return greetings.at(index);
    }

    case FAREWELL: {
        // Return a random farewell
        int index = QRandomGenerator::global()->bounded(farewells.size());
        return farewells.at(index);
    }

    case LIST_SPONSORS: {
        QList<Sponsor> sponsors = getSponsors();
        if (sponsors.isEmpty()) {
            return "There are no sponsors in the database.";
        }

        QString response = "Here are the sponsors in our database:\n";
        for (int i = 0; i < sponsors.size(); ++i) {
            response += QString("%1. %2 (Domain: %3)\n")
            .arg(i + 1)
                .arg(sponsors[i].getNom())
                .arg(sponsors[i].getDomaine());
        }
        return response;
    }

    case FIND_SPONSOR_BY_NAME: {
        QString name = extractName(input);
        if (name.isEmpty()) {
            return "I couldn't identify the sponsor name in your question. Please specify the name more clearly.";
        }

        Sponsor sponsor = getSponsorByName(name);
        if (sponsor.getNom().isEmpty()) {
            return QString("Sorry, I couldn't find a sponsor named '%1' in our database.").arg(name);
        }

        return QString("Sponsor: %1\nDomain: %2\nFounded: %3\nFinancial Capacity: %4\nType: %5")
            .arg(sponsor.getNom())
            .arg(sponsor.getDomaine())
            .arg(sponsor.getAnneeFondation())
            .arg(sponsor.getCapaciteFinanciere())
            .arg(sponsor.getTypeSponsoring());
    }

    case FIND_SPONSOR_BY_CODE: {
        QString code = extractCode(input);
        if (code.isEmpty()) {
            return "I couldn't identify the sponsor code in your question. Please provide a valid code.";
        }

        Sponsor sponsor = getSponsorByCode(code);
        if (sponsor.getCodeFiscal().isEmpty()) {
            return QString("Sorry, I couldn't find a sponsor with code '%1' in our database.").arg(code);
        }

        return QString("Sponsor: %1\nCode Fiscal: %2\nDomain: %3\nFounded: %4\nFinancial Capacity: %5\nType: %6")
            .arg(sponsor.getNom())
            .arg(sponsor.getCodeFiscal())
            .arg(sponsor.getDomaine())
            .arg(sponsor.getAnneeFondation())
            .arg(sponsor.getCapaciteFinanciere())
            .arg(sponsor.getTypeSponsoring());
    }

    case FIND_SPONSORS_BY_DOMAIN: {
        QString domain = extractDomain(input);
        if (domain.isEmpty()) {
            return "I couldn't identify the domain in your question. Please specify a valid domain.";
        }

        QList<Sponsor> sponsors = getSponsorsByDomain(domain);
        if (sponsors.isEmpty()) {
            return QString("Sorry, I couldn't find any sponsors in the '%1' domain.").arg(domain);
        }

        QString response = QString("Here are the sponsors in the '%1' domain:\n").arg(domain);
        for (int i = 0; i < sponsors.size(); ++i) {
            response += QString("%1. %2 (Founded: %3, Capacity: %4)\n")
            .arg(i + 1)
                .arg(sponsors[i].getNom())
                .arg(sponsors[i].getAnneeFondation())
                .arg(sponsors[i].getCapaciteFinanciere());
        }
        return response;
    }

    case FIND_SPONSORS_BY_CAPACITY: {
        QPair<double, double> range = extractCapacityRange(input);
        double min = range.first;
        double max = range.second;

        QString condition;
        if (min > 0 && max > 0) {
            condition = QString("CAPACITE_FINANCIERE BETWEEN %1 AND %2").arg(min).arg(max);
        } else if (min > 0) {
            condition = QString("CAPACITE_FINANCIERE >= %1").arg(min);
        } else if (max > 0) {
            condition = QString("CAPACITE_FINANCIERE <= %1").arg(max);
        } else {
            return "I couldn't determine the financial capacity range you're looking for.";
        }

        QList<Sponsor> sponsors = getSponsors(condition);
        if (sponsors.isEmpty()) {
            return "Sorry, I couldn't find any sponsors matching your financial capacity criteria.";
        }

        QString response = "Here are the sponsors matching your financial capacity criteria:\n";
        for (int i = 0; i < sponsors.size(); ++i) {
            response += QString("%1. %2 (Capacity: %3, Domain: %4)\n")
            .arg(i + 1)
                .arg(sponsors[i].getNom())
                .arg(sponsors[i].getCapaciteFinanciere())
                .arg(sponsors[i].getDomaine());
        }
        return response;
    }

    case BEST_SPONSOR: {
        Sponsor sponsor = getBestSponsor();
        if (sponsor.getNom().isEmpty()) {
            return "Sorry, I couldn't determine the best sponsor. The database might be empty.";
        }

        return QString("The top sponsor is %1 with a financial capacity of %2.\nDomain: %3\nFounded: %4\nType: %5")
            .arg(sponsor.getNom())
            .arg(sponsor.getCapaciteFinanciere())
            .arg(sponsor.getDomaine())
            .arg(sponsor.getAnneeFondation())
            .arg(sponsor.getTypeSponsoring());
    }

    case GET_CONTACT_INFO: {
        QString identifier = extractName(input);
        if (identifier.isEmpty()) {
            return "I couldn't identify which sponsor you want contact information for. Please specify a name or code.";
        }

        QString contactInfo = getContactInfo(identifier);
        if (contactInfo.isEmpty()) {
            return QString("Sorry, I couldn't find contact information for '%1'.").arg(identifier);
        }

        return contactInfo;
    }

    case UNKNOWN:
    default: {
        // Return a random unknown response
        int index = QRandomGenerator::global()->bounded(unknownResponses.size());
        return unknownResponses.at(index);
    }
    }
}

// Helper methods for database queries

QList<Sponsor> ChatBot::getSponsors(const QString &condition)
{
    QList<Sponsor> sponsors;
    QSqlQuery query;

    QString queryStr = "SELECT * FROM SPONSOR";
    if (!condition.isEmpty()) {
        queryStr += " WHERE " + condition;
    }
    queryStr += " ORDER BY NOM";

    if (!query.exec(queryStr)) {
        qDebug() << "ChatBot SQL Error in getSponsors(): " << query.lastError().text();
        return sponsors;
    }

    while (query.next()) {
        Sponsor sponsor;
        sponsor.setCodeFiscal(query.value("CODE_FISCAL").toString());
        sponsor.setNom(query.value("NOM").toString());
        sponsor.setEmail(query.value("EMAIL").toString());
        sponsor.setTelephone(query.value("TELEPHONE").toString());
        sponsor.setDomaine(query.value("DOMAINE").toString());
        sponsor.setAdresse(query.value("ADRESSE").toString());
        sponsor.setAnneeFondation(query.value("ANNEE_FONDATION").toInt());
        sponsor.setTypeSponsoring(query.value("TYPE_DE_SPONSORING").toString());
        sponsor.setCapaciteFinanciere(query.value("CAPACITE_FINANCIERE").toDouble());

        sponsors.append(sponsor);
    }

    return sponsors;
}

Sponsor ChatBot::getSponsorByCode(const QString &code)
{
    Sponsor sponsor;
    if (code.isEmpty()) {
        return sponsor;
    }

    sponsor.load(code);
    return sponsor;
}

Sponsor ChatBot::getSponsorByName(const QString &name)
{
    Sponsor sponsor;
    if (name.isEmpty()) {
        return sponsor;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSOR WHERE NOM LIKE :name LIMIT 1");
    query.bindValue(":name", "%" + name + "%");

    if (!query.exec()) {
        qDebug() << "ChatBot SQL Error in getSponsorByName(): " << query.lastError().text();
        return sponsor;
    }

    if (query.next()) {
        sponsor.setCodeFiscal(query.value("CODE_FISCAL").toString());
        sponsor.setNom(query.value("NOM").toString());
        sponsor.setEmail(query.value("EMAIL").toString());
        sponsor.setTelephone(query.value("TELEPHONE").toString());
        sponsor.setDomaine(query.value("DOMAINE").toString());
        sponsor.setAdresse(query.value("ADRESSE").toString());
        sponsor.setAnneeFondation(query.value("ANNEE_FONDATION").toInt());
        sponsor.setTypeSponsoring(query.value("TYPE_DE_SPONSORING").toString());
        sponsor.setCapaciteFinanciere(query.value("CAPACITE_FINANCIERE").toDouble());
    }

    return sponsor;
}

QList<Sponsor> ChatBot::getSponsorsByDomain(const QString &domain)
{
    QString actualDomain = domain;

    // Try to match domain keywords
    for (auto it = domainKeywords.begin(); it != domainKeywords.end(); ++it) {
        const QString &dbDomain = it.key();
        const QStringList &keywords = it.value();

        for (const QString &keyword : keywords) {
            if (domain.contains(keyword, Qt::CaseInsensitive)) {
                actualDomain = dbDomain;
                break;
            }
        }

        if (actualDomain != domain) {
            break;
        }
    }

    return getSponsors(QString("DOMAINE LIKE '%%1%'").arg(actualDomain));
}

QList<Sponsor> ChatBot::getSponsorsByCapacityRange(double min, double max)
{
    QString condition;

    if (min > 0 && max > 0) {
        condition = QString("CAPACITE_FINANCIERE BETWEEN %1 AND %2").arg(min).arg(max);
    } else if (min > 0) {
        condition = QString("CAPACITE_FINANCIERE >= %1").arg(min);
    } else if (max > 0) {
        condition = QString("CAPACITE_FINANCIERE <= %1").arg(max);
    }

    return getSponsors(condition);
}

Sponsor ChatBot::getBestSponsor()
{
    Sponsor sponsor;

    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSOR ORDER BY CAPACITE_FINANCIERE DESC LIMIT 1");

    if (!query.exec()) {
        qDebug() << "ChatBot SQL Error in getBestSponsor(): " << query.lastError().text();
        return sponsor;
    }

    if (query.next()) {
        sponsor.setCodeFiscal(query.value("CODE_FISCAL").toString());
        sponsor.setNom(query.value("NOM").toString());
        sponsor.setEmail(query.value("EMAIL").toString());
        sponsor.setTelephone(query.value("TELEPHONE").toString());
        sponsor.setDomaine(query.value("DOMAINE").toString());
        sponsor.setAdresse(query.value("ADRESSE").toString());
        sponsor.setAnneeFondation(query.value("ANNEE_FONDATION").toInt());
        sponsor.setTypeSponsoring(query.value("TYPE_DE_SPONSORING").toString());
        sponsor.setCapaciteFinanciere(query.value("CAPACITE_FINANCIERE").toDouble());
    }

    return sponsor;
}

QString ChatBot::getContactInfo(const QString &identifier)
{
    // Try to find sponsor by code first
    Sponsor sponsor = getSponsorByCode(identifier);

    // If not found, try by name
    if (sponsor.getNom().isEmpty()) {
        sponsor = getSponsorByName(identifier);
    }

    if (sponsor.getNom().isEmpty()) {
        return QString();
    }

    return QString("Contact information for %1:\nEmail: %2\nPhone: %3\nAddress: %4")
        .arg(sponsor.getNom())
        .arg(sponsor.getEmail())
        .arg(sponsor.getTelephone())
        .arg(sponsor.getAdresse());
}

// Helper methods for entity extraction

QString ChatBot::extractName(const QString &input)
{
    QRegularExpression namePattern("(named|called|with name|about|for|of)\\s+([a-zA-Z0-9\\s&]+)(\\b|$)",
                                   QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = namePattern.match(input);

    if (match.hasMatch()) {
        return match.captured(2).trimmed();
    }

    return QString();
}

QString ChatBot::extractCode(const QString &input)
{
    QRegularExpression codePattern("(code|fiscal code|registration|cr)\\s+([A-Z0-9]+)(\\b|$)",
                                   QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = codePattern.match(input);

    if (match.hasMatch()) {
        return match.captured(2).trimmed();
    }

    return QString();
}

QString ChatBot::extractDomain(const QString &input)
{
    QRegularExpression domainPattern("(in|from|working in|specialized in)\\s+([a-zA-Z\\s&]+)(\\b|$)",
                                     QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = domainPattern.match(input);

    if (match.hasMatch()) {
        QString domainText = match.captured(2).trimmed();

        // Check for domain keywords
        for (auto it = domainKeywords.begin(); it != domainKeywords.end(); ++it) {
            const QString &dbDomain = it.key();
            const QStringList &keywords = it.value();

            for (const QString &keyword : keywords) {
                if (domainText.contains(keyword, Qt::CaseInsensitive)) {
                    return dbDomain;
                }
            }
        }

        return domainText;
    }

    return QString();
}

QPair<double, double> ChatBot::extractCapacityRange(const QString &input)
{
    QPair<double, double> result(0.0, 0.0);

    QRegularExpression rangePattern("(between|above|below|over|under)\\s+([0-9.,]+)\\s*(and|to)?\\s*([0-9.,]+)?",
                                    QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = rangePattern.match(input);

    if (match.hasMatch()) {
        QString comparator = match.captured(1).toLower();
        QString firstValue = match.captured(2).replace(",", "");
        QString secondValue = match.captured(4).replace(",", "");

        double value1 = firstValue.toDouble();
        double value2 = secondValue.toDouble();

        if (comparator == "between" && value2 > 0) {
            result.first = value1;
            result.second = value2;
        } else if (comparator == "above" || comparator == "over") {
            result.first = value1;
        } else if (comparator == "below" || comparator == "under") {
            result.second = value1;
        }
    }

    return result;
}
QString ChatBot::getResponse(const QString &message)
{
    // This is a simple implementation - you should expand it based on your needs

    QString messageLower = message.toLower();

    // Check for basic greetings
    if (messageLower.contains("hello") || messageLower.contains("hi") || messageLower == "hey") {
        return "Hello! How can I help you with sponsors today?";
    }

    // Sponsors listing request
    if (messageLower.contains("list") && messageLower.contains("sponsor")) {
        return "Here are our main sponsors:\n"
               "- TechGlobal (Technology)\n"
               "- HealthPlus (Healthcare)\n"
               "- EcoFriendly (Environmental)\n"
               "- FinanceFirst (Financial Services)\n"
               "- BuildIt (Construction)\n"
               "Would you like more details about any of them?";
    }

    // Best sponsor query
    if (messageLower.contains("best sponsor")) {
        return "All our sponsors are valuable partners! However, TechGlobal has been our most engaged sponsor this year with over $200,000 in support and active participation in all our events.";
    }

    // Technology sponsors
    if ((messageLower.contains("tech") || messageLower.contains("technology")) && messageLower.contains("sponsor")) {
        return "Our technology sponsors include:\n"
               "- TechGlobal (Software Solutions, Capacity: 250,000)\n"
               "- DigiCorp (Hardware Manufacturing, Capacity: 150,000)\n"
               "- NetSecure (Cybersecurity, Capacity: 100,000)";
    }

    // Capacity query
    if (messageLower.contains("capacity") && messageLower.contains("above")) {
        QRegularExpression regex("(\\d+)");
        QRegularExpressionMatch match = regex.match(messageLower);
        QString threshold = match.hasMatch() ? match.captured(1) : "100000";

        return "Sponsors with capacity above " + threshold + ":\n"
                                                             "- TechGlobal (Capacity: 250,000)\n"
                                                             "- HealthPlus (Capacity: 200,000)\n"
                                                             "- DigiCorp (Capacity: 150,000)\n"
                                                             "- FinanceFirst (Capacity: 120,000)";
    }

    // Contact information
    if (messageLower.contains("contact") && messageLower.contains("information")) {
        if (messageLower.contains("techglobal")) {
            return "TechGlobal Contact Information:\n"
                   "Email: partnerships@techglobal.com\n"
                   "Phone: (555) 123-4567\n"
                   "Contact Person: Sarah Johnson, Partnerships Director";
        }
        else if (messageLower.contains("healthplus")) {
            return "HealthPlus Contact Information:\n"
                   "Email: sponsors@healthplus.org\n"
                   "Phone: (555) 987-6543\n"
                   "Contact Person: Dr. Michael Chen, Community Outreach";
        }
        else {
            return "Please specify which sponsor you need contact information for. For example, 'Contact information for TechGlobal'.";
        }
    }

    // Find sponsor by code
    if (messageLower.contains("code")) {
        if (messageLower.contains("tg2023")) {
            return "Sponsor Code TG2023 belongs to TechGlobal, a technology company focused on software solutions.";
        }
        else if (messageLower.contains("hp2023")) {
            return "Sponsor Code HP2023 belongs to HealthPlus, a healthcare provider focused on community wellness.";
        }
        else {
            return "I couldn't find a sponsor with that code. Please check the code and try again. Valid codes include TG2023, HP2023, EF2023, FF2023, and BI2023.";
        }
    }

    // Default response
    return "I'm not sure I understand your question about sponsors. You can ask me about listing sponsors, "
           "finding sponsors in specific industries, checking sponsor capacities, or getting contact information.";
}
