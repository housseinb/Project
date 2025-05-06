#include "chatbot.h"
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <algorithm>
#include <QRegularExpression>
#include <QDateTime>


Chatbot::Chatbot(QSqlDatabase& database) : db(database), currentState(GREETING) {
    // Initialize common responses
    initializeCommonResponses();
}

Chatbot::~Chatbot() {}

void Chatbot::initializeCommonResponses() {
    // Greetings and common phrases
    commonResponses = {
        {"hello", {"Hello! How can I assist you with sponsors or projects today?", GREETING}},
        {"hi", {"Hi there! I'm your sponsor and project assistant. What can I do for you?", GREETING}},
        {"hey", {"Hey! Ready to help with sponsors or projects. What do you need?", GREETING}},
        {"good morning", {"Good morning! How can I help you with sponsors or projects today?", GREETING}},
        {"good afternoon", {"Good afternoon! What sponsor or project information do you need?", GREETING}},
        {"good evening", {"Good evening! How may I assist you with sponsors or projects?", GREETING}},
        {"how are you", {"I'm just a program, so I don't have feelings, but I'm ready to help you with any sponsor or project queries!", GREETING}},
        {"what's up", {"Ready to assist with sponsors and projects! What do you need?", GREETING}},
        {"how's it going", {"All systems operational! How can I help with sponsors or projects today?", GREETING}},
        {"thank you", {"You're welcome! Is there anything else I can help you with?", GREETING}},
        {"thanks", {"My pleasure! Let me know if you need anything else about sponsors or projects.", GREETING}},
        {"bye", {"Goodbye! Feel free to return if you have more questions about sponsors or projects.", GREETING}},
        {"goodbye", {"Farewell! Remember I'm here for all your sponsor and project needs.", GREETING}},
        {"exit", {"Closing our chat. You can always return for more sponsor or project assistance!", GREETING}}
    };

    // Help responses
    helpResponses = {
        "📋 I can help with everything related to sponsors and projects. Here's what I can do:\n",

        "🔹 SPONSOR INFORMATION:",
        "   • Show sponsor details: 'Show details for [name/code]'",
        "   • Get specific info: 'What's the email/phone/address of [sponsor]?'",
        "   • List sponsors: 'List all sponsors', 'Show sponsors in [domain]'",
        "   • Financial queries: 'Sponsors with capacity over $X', 'Richest sponsors'",
        "   • Search: 'Find sponsors in tech domain', 'Search for sponsor [name]'\n",

        "🔹 PROJECT RECOMMENDATIONS:",
        "   • General: 'Recommend a project', 'Find projects for [purpose]'",
        "   • By domain: 'Tech projects', 'Health-related projects'",
        "   • By budget: 'Projects under $50k', 'Affordable projects'",
        "   • By features: 'Projects for students', 'Local business solutions'\n",

        "🔹 STATISTICS & ANALYTICS:",
        "   • Counts: 'How many sponsors?', 'Number of projects'",
        "   • Financials: 'Average sponsor capacity', 'Total sponsorship value'",
        "   • Domain stats: 'Sponsor distribution by domain'",
        "   • Top lists: 'Top 5 sponsors', 'Most expensive projects'\n",

        "🔹 FILTERED SEARCHES:",
        "   • Combined filters: 'Tech sponsors with capacity over $100k'",
        "   • Project filters: 'Education projects under $30k'",
        "   • Advanced: 'Sponsors founded after 2010 in health domain'\n",

        "🔹 GENERAL COMMANDS:",
        "   • 'Help' - Show this message",
        "   • 'Restart' - Start a new conversation",
        "   • 'Exit' - End the chat session",
        "   • 'Menu' - Return to main options\n",

        "💡 Examples:",
        "   • 'Show details for sponsor TECH2023'",
        "   • 'List all health sponsors with capacity over $50k'",
        "   • 'Recommend an affordable project for local businesses'",
        "   • 'What's the average sponsor capacity in tech?'\n",

        "What would you like assistance with today?"
    };
}

QStringList Chatbot::tokenizeInput(const QString &input) {
    QString cleaned = input.toLower()
    .replace(QRegularExpression("[^a-z0-9\\s]"), " ")
        .replace("'", "")
        .replace("\"", "")
        .simplified();
    return cleaned.split(' ', Qt::SkipEmptyParts);
}

bool Chatbot::isCommonPhrase(const QString &input) {
    QString lowercase = input.toLower().trimmed();
    return commonResponses.contains(lowercase);
}

QString Chatbot::getCommonResponse(const QString &input) {
    QString lowercase = input.toLower().trimmed();
    if (commonResponses.contains(lowercase)) {
        currentState = commonResponses[lowercase].second;
        return commonResponses[lowercase].first;
    }
    return "";
}

bool Chatbot::shouldStartProjectRecommendation(const QString &input) {
    QString lowercase = input.toLower();

    // Direct recommendation phrases
    static const QStringList recommendationPhrases = {
        "recommend", "suggest", "find", "need a project", "want a project",
        "looking for a project", "searching for a project", "help me find",
        "suitable project", "project idea", "project suggestion", "recommend me",
        "what project", "which project", "can you recommend", "i need",
        "i want", "how about", "do you have", "any projects for",
        "projects about", "projects related to", "show me projects",
        "give me projects", "list projects", "display projects"
    };

    for (const QString &phrase : recommendationPhrases) {
        if (lowercase.contains(phrase)) {
            return true;
        }
    }

    return false;
}

bool Chatbot::containsSponsorInfoRequest(const QString &input) {
    QString lowercase = input.toLower();

    // Check for sponsor keyword with info request
    if (!lowercase.contains("sponsor")) {
        return false;
    }

    static const QStringList infoRequestPhrases = {
        "show", "detail", "list", "all", "email", "mail", "phone", "telephone",
        "address", "capacity", "domain", "type", "year", "info", "display",
        "get", "see", "view", "what is", "who is", "tell me about", "information",
        "contact", "number", "how much", "financial", "founding", "history",
        "about", "data", "record", "profile"
    };

    for (const QString &phrase : infoRequestPhrases) {
        if (lowercase.contains(phrase)) {
            return true;
        }
    }

    return false;
}

bool Chatbot::isStatisticsRequest(const QString &input) {
    QString lowercase = input.toLower();

    static const QStringList statPhrases = {
        "stat", "statistic", "data", "number", "how many", "count", "total",
        "average", "mean", "median", "percentage", "ratio", "distribution",
        "breakdown", "analysis", "report", "summarize", "overview", "metrics",
        "figure", "numbers", "quantity", "amount", "volume", "capacity"
    };

    for (const QString &phrase : statPhrases) {
        if (lowercase.contains(phrase)) {
            return true;
        }
    }

    return lowercase.contains("sponsor") && (
               lowercase.contains("info") ||
               lowercase.contains("data") ||
               lowercase.contains("number") ||
               lowercase.contains("how many")
               );
}

bool Chatbot::isProjectRecommendationWithFilters(const QString &input) {
    bool hasRecommendationIntent = shouldStartProjectRecommendation(input) ||
                                   input.contains("project");

    static const QStringList filterPhrases = {
        "under", "budget", "domain", "tech", "health", "education", "finance",
        "cost", "price", "cheap", "expensive", "affordable", "less than",
        "more than", "over", "below", "about", "around", "approximately",
        "near", "close to", "between", "range", "minimum", "maximum",
        "at least", "at most", "up to", "starting from", "type", "kind",
        "category", "field", "area", "sector", "industry", "for", "targeting",
        "aimed at", "intended for", "designed for", "suitable for"
    };

    bool hasFilters = false;
    for (const QString &phrase : filterPhrases) {
        if (input.contains(phrase)) {
            hasFilters = true;
            break;
        }
    }

    return hasRecommendationIntent && hasFilters;
}

QString Chatbot::extractFieldFromQuery(const QString &query, const QStringList &fields) {
    QString lowercaseQuery = query.toLower();
    for (const QString &field : fields) {
        if (lowercaseQuery.contains(field.toLower())) {
            return field;
        }
    }
    return "";
}

QString Chatbot::extractSponsorIdentifier(const QString &query) {
    QString simplified = query;

    // Remove common words that might interfere with sponsor identification
    simplified.remove(QRegularExpression(
        "email|phone|telephone|address|capacity|domain|type|year|founding|financial|"
        "of|for|sponsor|display|show|get|details|see|about|info|information|contact|"
        "what|who|tell|me|give|list|all|every|the|a|an|and|or|but|with|regarding|"
        "concerning|related|to|sponsoring|sponsorship",
        QRegularExpression::CaseInsensitiveOption));

    // Remove special characters and extra spaces
    simplified.remove(QRegularExpression("[^\\w\\s]"));
    simplified = simplified.simplified();

    return simplified.trimmed();
}

int Chatbot::extractProjectReference(const QString &input) {
    // First try to extract by ID pattern
    QRegularExpression projectIdRegex("project\\s*(?:number|id|no|#)?\\s*(\\d+)",
                                      QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = projectIdRegex.match(input);

    if (match.hasMatch()) {
        return match.captured(1).toInt();
    }

    // If no ID found, try to match by name
    QSqlQuery query(db);
    query.prepare("SELECT ID_PROJET, NOM_PROJET FROM PROJET");

    if (!query.exec()) {
        qDebug() << "PROJET query failed:" << query.lastError().text();
        return -1;
    }

    QString lowercaseInput = input.toLower();
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString().toLower();

        if (lowercaseInput.contains(name)) {
            return id;
        }
    }

    return -1;
}

QString Chatbot::processInput(const QString &userInput) {
    QString response;
    QString lowercaseInput = userInput.toLower().trimmed();

    // Handle empty inputs
    if (lowercaseInput.isEmpty()) {
        switch (currentState) {
        case ASK_PROBLEM:
            return "Could you please tell me what problem you're trying to solve?";
        case ASK_AUDIENCE:
            return "I need to know your target audience to recommend the right projects. Who are you building this for?";
        case ASK_MARKET_ANALYSIS:
            return "Please tell me about your target market or region.";
        case ASK_COMPETITION:
            return "Could you share any information about existing competition in this space?";
        default:
            return "Hello! How can I help you today with projects or sponsors?";
        }
    }

    // Check for common phrases first
    if (isCommonPhrase(lowercaseInput)) {
        return getCommonResponse(lowercaseInput);
    }

    // Handle help requests
    if (lowercaseInput == "help" || lowercaseInput == "options" ||
        lowercaseInput == "what can you do" || lowercaseInput == "menu") {
        return helpResponses.join("\n");
    }

    // Handle statistics requests
    if (isStatisticsRequest(lowercaseInput)) {
        return getAdvancedSponsorStatistics(lowercaseInput);
    }

    // Handle sponsor information requests
    if (containsSponsorInfoRequest(lowercaseInput)) {
        return handleAdvancedSponsorQuery(lowercaseInput);
    }

    // Handle project recommendations with filters
    if (isProjectRecommendationWithFilters(lowercaseInput)) {
        return handleFilteredProjectRecommendation(lowercaseInput);
    }

    // Handle conversation reset
    if (lowercaseInput == "restart" || lowercaseInput == "reset" ||
        lowercaseInput == "start over" || lowercaseInput == "new search") {
        resetConversation();
        return "Let's start fresh! What problem or need are you trying to solve with your project?";
    }

    // Start project recommendation flow
    if (shouldStartProjectRecommendation(lowercaseInput)) {
        resetConversation();
        response = "Great! I'd be happy to help you find the perfect project.\n"
                   "First, what problem or need are you trying to solve?";
        currentState = ASK_PROBLEM;
        return response;
    }









    // Process based on current state
    // Process based on current state
    switch (currentState) {
    case GREETING:
        response = "Hello! I'm your advanced project and sponsor assistant. I can help with:\n"
                   "1. Finding suitable projects (say 'recommend a project')\n"
                   "2. Detailed sponsor information (try 'show sponsor details')\n"
                   "3. Comprehensive statistics (try 'sponsor stats')\n"
                   "4. Filtered project searches (e.g., 'tech projects under $50k')\n\n"
                   "How can I assist you today?";
        break;

    case ASK_PROBLEM:
        userCriteria["problem"] = userInput.trimmed();
        response = "Who is your target audience? (PUBLIC_CIBLE)";
        currentState = ASK_AUDIENCE;
        break;

    case ASK_AUDIENCE:
        userCriteria["audience"] = userInput.trimmed();
        response = "What value proposition does your project offer? (PROPOSITION_DE_VALEUR)";
        currentState = ASK_VALUE_PROP;
        break;

    case ASK_VALUE_PROP:
        userCriteria["value_prop"] = userInput.trimmed();
        response = "What market analysis have you done? (ANALYSE_DU_MARCHE)";
        currentState = ASK_MARKET_ANALYSIS;
        break;

    case ASK_MARKET_ANALYSIS:
        userCriteria["market"] = userInput.trimmed();
        response = "What competition exists for your project? (CONCURRENCE)";
        currentState = ASK_COMPETITION;
        break;

    case ASK_COMPETITION: {
        userCriteria["competition"] = userInput.trimmed();
        QVector<int> recommended = recommendProjects();

        if (recommended.isEmpty()) {
            response = "Based on your criteria, I couldn't find exact matches. Here are your options:\n"
                       "1. Try again with different criteria (say 'restart')\n"
                       "2. Get filtered recommendations (e.g., 'tech projects under $50k')\n"
                       "3. Browse sponsor information (e.g., 'list all sponsors')\n"
                       "4. Ask for help (say 'help')";
        } else {
            response = "Here are some recommended projects based on your criteria:\n\n";
            for (int projectId : recommended) {
                response += getProjectInfo(projectId);
                if (projectId != recommended.last()) {
                    response += "\n──────────\n";
                }
            }
            response += "\n\nWould you like to:\n"
                        "1. Get more details about a specific project? (say 'tell me more about project X')\n"
                        "2. Restart with new criteria (say 'restart')\n"
                        "3. Get filtered projects (e.g., 'tech projects under $30k')\n"
                        "4. Learn about sponsors (e.g., 'show sponsor details')";
        }
        currentState = RECOMMEND;
        break;
    }

    case RECOMMEND:
        if (lowercaseInput.contains("tell me more") ||
            lowercaseInput.contains("more details") ||
            lowercaseInput.contains("interested in") ||
            lowercaseInput.contains("like project") ||
            lowercaseInput.contains("about project")) {

            int projectId = extractProjectReference(lowercaseInput);
            if (projectId > 0) {
                return getDetailedProjectInfo(projectId);
            } else {
                return "Which project would you like to know more about? You can mention it by name or number.";
            }
        } else {
            response = "I can help you with:\n"
                       "- More project recommendations (specific filters welcome)\n"
                       "- Detailed sponsor information\n"
                       "- Start over with new criteria (say 'restart')\n"
                       "What would you like to do?";
            currentState = GREETING;
        }
        break;

    case SPONSOR_QUERY:
    case PROJECT_FILTER:
        response = "I'm here to help with projects and sponsors. What else would you like to know?";
        currentState = GREETING;
        break;
    }

    return response;
}

QString Chatbot::handleAdvancedSponsorQuery(const QString &query) {
    currentState = SPONSOR_QUERY;

    // Handle "list all sponsors" variations
    if (query.contains("list all") || query.contains("show every") ||
        query.contains("display all") || query.contains("all sponsors") ||
        query.contains("every sponsor") || query.contains("complete list")) {
        return getAllSponsorsInfo();
    }

    // Handle "top sponsors by capacity" queries
    if (query.contains("top sponsor") || query.contains("highest capacity") ||
        query.contains("richest sponsor") || query.contains("most financial") ||
        query.contains("largest sponsor") || query.contains("biggest sponsor")) {
        return getTopSponsorsByCapacity();
    }

    // Handle "sponsors in domain" queries
    QRegularExpression domainRegex("(sponsors? (?:in|for|about|related to) (tech|technology|health|education|finance|retail|ecommerce|media|entertainment|automotive|food|real estate|other))",
                                   QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch domainMatch = domainRegex.match(query);
    if (domainMatch.hasMatch()) {
        QString domain = domainMatch.captured(1);
        return getSponsorsByDomain(domain);
    }

    // Handle "sponsors with capacity" queries
    QRegularExpression capacityRegex("(sponsors? (?:with|having) capacity (over|above|more than|under|below|less than) \\$?([\\d,]+(?:k| thousand| million)?)",
                                     QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch capacityMatch = capacityRegex.match(query);
    if (capacityMatch.hasMatch()) {
        QString comparison = capacityMatch.captured(1).toLower();
        QString amountStr = capacityMatch.captured(2);
        double amount = parseFinancialAmount(amountStr);

        if (amount > 0) {
            return getSponsorsByCapacity(comparison, amount);
        }
    }

    // Handle "show sponsor X" with more variations
    QRegularExpression showSponsorRegex("(show|display|get|see|view|find|list|what is|who is|tell me about)\\s+(?:sponsor|details|info|information)\\s+(?:for\\s+)?([\\w\\s]+)",
                                        QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch showMatch = showSponsorRegex.match(query);

    if (showMatch.hasMatch()) {
        QString sponsorIdentifier = showMatch.captured(2).trimmed();
        return getSponsorDetails(sponsorIdentifier);
    }

    // Enhanced field extraction with more variations
    QStringList fields = {"email", "phone", "telephone", "address", "capacity",
                          "domain", "type", "year", "founding", "financial",
                          "contact", "number", "budget", "money", "fund",
                          "location", "city", "country", "postal", "zip",
                          "code", "fiscal", "id", "identifier", "name"};
    QString fieldRequest = extractFieldFromQuery(query, fields);

    if (!fieldRequest.isEmpty()) {
        QString identifier = extractSponsorIdentifier(query);

        if (fieldRequest == "year" || fieldRequest == "founding") {
            return getSponsorDetails(identifier, "year");
        } else if (fieldRequest == "financial" || fieldRequest == "capacity" ||
                   fieldRequest == "budget" || fieldRequest == "money" || fieldRequest == "fund") {
            return getSponsorDetails(identifier, "capacity");
        } else if (fieldRequest == "phone" || fieldRequest == "telephone" || fieldRequest == "number") {
            return getSponsorDetails(identifier, "phone");
        } else if (fieldRequest == "address" || fieldRequest == "location" ||
                   fieldRequest == "city" || fieldRequest == "country" ||
                   fieldRequest == "postal" || fieldRequest == "zip") {
            return getSponsorDetails(identifier, "address");
        } else if (fieldRequest == "code" || fieldRequest == "fiscal" ||
                   fieldRequest == "id" || fieldRequest == "identifier") {
            return getSponsorDetails(identifier, "code");
        }

        return getSponsorDetails(identifier, fieldRequest);
    }

    // Enhanced default response
    return "I can help with detailed sponsor information. Try these examples:\n"
           "- \"Show sponsor ABC123\" or \"Display details for XYZ Corp\"\n"
           "- \"Email of sponsor TECH2023\" or \"Phone for Microsoft\"\n"
           "- \"List all sponsors in health domain\"\n"
           "- \"Find sponsors with capacity over $100k\"\n"
           "- \"Which sponsor has the highest financial capacity?\"\n"
           "- \"Sponsor statistics\" or \"How many sponsors are there?\"";
}




double Chatbot::parseFinancialAmount(const QString &amountStr) {
    QString cleanStr = amountStr.toLower()
    .replace(",", "")
        .replace("k", "000")
        .replace(" thousand", "000")
        .replace(" million", "000000");

    bool ok;
    double amount = cleanStr.toDouble(&ok);
    return ok ? amount : 0.0;
}

QString Chatbot::getSponsorDetails(const QString &identifier, const QString &specificField) {
    QSqlQuery sqlQuery(db);

    // Try to match by fiscal code first
    sqlQuery.prepare("SELECT * FROM SPONSOR WHERE CODE_FISCAL = :identifier");
    sqlQuery.bindValue(":identifier", identifier);

    if (!sqlQuery.exec() || !sqlQuery.next()) {
        // If not found by code, try by name
        sqlQuery.prepare("SELECT * FROM SPONSOR WHERE NOM LIKE :nameMatch");
        sqlQuery.bindValue(":nameMatch", "%" + identifier + "%");

        if (!sqlQuery.exec() || !sqlQuery.next()) {
            return QString("No sponsor found matching: %1\nTry using exact fiscal code or name.").arg(identifier);
        }
    }

    if (!specificField.isEmpty()) {
        QString fieldValue;
        QString fieldDisplayName;

        if (specificField == "email") {
            fieldValue = sqlQuery.value("EMAIL").toString();
            fieldDisplayName = "Email";
        }
        else if (specificField == "phone" || specificField == "telephone") {
            fieldValue = sqlQuery.value("TELEPHONE").toString();
            fieldDisplayName = "Phone";
        }
        else if (specificField == "address") {
            fieldValue = sqlQuery.value("ADRESSE").toString();
            fieldDisplayName = "Address";
        }
        else if (specificField == "capacity") {
            double capacity = sqlQuery.value("CAPACITE_FINANCIERE").toDouble();
            fieldValue = QString("$%1").arg(capacity, 0, 'f', 2);
            fieldDisplayName = "Financial Capacity";
        }
        else if (specificField == "domain") {
            fieldValue = sqlQuery.value("DOMAINE").toString();
            fieldDisplayName = "Domain";
        }
        else if (specificField == "type") {
            fieldValue = sqlQuery.value("TYPE_DE_SPONSORING").toString();
            fieldDisplayName = "Sponsoring Type";
        }
        else if (specificField == "year" || specificField == "founding") {
            fieldValue = sqlQuery.value("ANNEE_FONDATION").toString();
            fieldDisplayName = "Founding Year";
        }
        else if (specificField == "code") {
            fieldValue = sqlQuery.value("CODE_FISCAL").toString();
            fieldDisplayName = "Fiscal Code";
        }

        if (!fieldValue.isEmpty()) {
            return QString("Sponsor %1 (%2):\n%3: %4")
            .arg(sqlQuery.value("NOM").toString())
                .arg(sqlQuery.value("CODE_FISCAL").toString())
                .arg(fieldDisplayName)
                .arg(fieldValue);
        }
    }

    // Full details response
    QString response = "📋 Sponsor Details:\n";
    response += QString("• Name: %1\n").arg(sqlQuery.value("NOM").toString());
    response += QString("• Fiscal Code: %1\n").arg(sqlQuery.value("CODE_FISCAL").toString());
    response += QString("• Email: %1\n").arg(sqlQuery.value("EMAIL").toString());
    response += QString("• Phone: %1\n").arg(sqlQuery.value("TELEPHONE").toString());
    response += QString("• Domain: %1\n").arg(sqlQuery.value("DOMAINE").toString());
    response += QString("• Address: %1\n").arg(sqlQuery.value("ADRESSE").toString());
    response += QString("• Founding Year: %1\n").arg(sqlQuery.value("ANNEE_FONDATION").toInt());
    response += QString("• Sponsoring Type: %1\n").arg(sqlQuery.value("TYPE_DE_SPONSORING").toString());
    response += QString("• Financial Capacity: $%1\n").arg(sqlQuery.value("CAPACITE_FINANCIERE").toDouble(), 0, 'f', 2);

    return response;
}

QString Chatbot::getAllSponsorsInfo() {
    QSqlQuery query(db);
    if (!query.exec("SELECT NOM, CODE_FISCAL, DOMAINE, CAPACITE_FINANCIERE, EMAIL, TELEPHONE FROM SPONSOR ORDER BY NOM")) {
        return "Error retrieving sponsor list: " + query.lastError().text();
    }

    int sponsorCount = 0;
    QString response = "📜 All Sponsors:\n\n";

    while (query.next()) {
        sponsorCount++;
        QString name = query.value(0).toString();
        QString code = query.value(1).toString();
        QString domain = query.value(2).toString();
        double capacity = query.value(3).toDouble();
        QString email = query.value(4).toString();
        QString phone = query.value(5).toString();

        response += QString("➤ %1\n  Code: %2\n  Domain: %3\n  Capacity: $%4\n  Email: %5\n  Phone: %6\n\n")
                        .arg(name)
                        .arg(code)
                        .arg(domain)
                        .arg(capacity, 0, 'f', 2)
                        .arg(email)
                        .arg(phone);
    }

    if (sponsorCount == 0) {
        response = "No sponsors found in the database.";
    } else {
        response += QString("───\nTotal Sponsors: %1").arg(sponsorCount);
    }

    return response;
}

QString Chatbot::getTopSponsorsByCapacity(int limit) {
    QSqlQuery query(db);
    query.prepare("SELECT NOM, CODE_FISCAL, CAPACITE_FINANCIERE FROM SPONSOR "
                  "ORDER BY CAPACITE_FINANCIERE DESC LIMIT :limit");
    query.bindValue(":limit", limit);

    if (!query.exec()) {
        return "Error retrieving top sponsors: " + query.lastError().text();
    }

    QString response = QString("🏆 Top %1 Sponsors by Financial Capacity:\n\n").arg(limit);
    int rank = 1;

    while (query.next()) {
        QString name = query.value(0).toString();
        QString code = query.value(1).toString();
        double capacity = query.value(2).toDouble();

        response += QString("%1. %2 (%3): $%4\n")
                        .arg(rank++)
                        .arg(name)
                        .arg(code)
                        .arg(capacity, 0, 'f', 2);
    }

    if (rank == 1) {
        return "No sponsors found in the database.";
    }

    return response;
}

QString Chatbot::getSponsorsByDomain(const QString &domain) {
    QSqlQuery query(db);
    query.prepare("SELECT NOM, CODE_FISCAL, CAPACITE_FINANCIERE FROM SPONSOR "
                  "WHERE DOMAINE = :domain ORDER BY NOM");
    query.bindValue(":domain", domain);

    if (!query.exec()) {
        return "Error retrieving sponsors by domain: " + query.lastError().text();
    }

    QString response = QString("🏷️ Sponsors in %1 Domain:\n\n").arg(domain);
    int count = 0;

    while (query.next()) {
        count++;
        QString name = query.value(0).toString();
        QString code = query.value(1).toString();
        double capacity = query.value(2).toDouble();

        response += QString("• %1 (%2): $%3\n")
                        .arg(name)
                        .arg(code)
                        .arg(capacity, 0, 'f', 2);
    }

    if (count == 0) {
        return QString("No sponsors found in the %1 domain.").arg(domain);
    }

    response += QString("\nTotal: %1 sponsors").arg(count);
    return response;
}

QString Chatbot::getSponsorsByCapacity(const QString &comparison, double amount) {
    QString queryCondition;
    QString comparisonText;

    if (comparison == "over" || comparison == "above" || comparison == "more than") {
        queryCondition = "CAPACITE_FINANCIERE > :amount";
        comparisonText = "above";
    } else {
        queryCondition = "CAPACITE_FINANCIERE < :amount";
        comparisonText = "below";
    }

    QSqlQuery query(db);
    query.prepare("SELECT NOM, CODE_FISCAL, CAPACITE_FINANCIERE FROM SPONSOR "
                  "WHERE " + queryCondition + " ORDER BY CAPACITE_FINANCIERE DESC");
    query.bindValue(":amount", amount);

    if (!query.exec()) {
        return "Error retrieving sponsors by capacity: " + query.lastError().text();
    }

    QString response = QString("💰 Sponsors with capacity %1 $%2:\n\n")
                           .arg(comparisonText)
                           .arg(amount, 0, 'f', 2);
    int count = 0;
    double totalCapacity = 0;

    while (query.next()) {
        count++;
        QString name = query.value(0).toString();
        QString code = query.value(1).toString();
        double capacity = query.value(2).toDouble();
        totalCapacity += capacity;

        response += QString("• %1 (%2): $%3\n")
                        .arg(name)
                        .arg(code)
                        .arg(capacity, 0, 'f', 2);
    }

    if (count == 0) {
        return QString("No sponsors found with capacity %1 $%2.")
        .arg(comparisonText)
            .arg(amount, 0, 'f', 2);
    }

    double averageCapacity = totalCapacity / count;

    response += QString("\n📊 Summary:\n");
    response += QString("• Total Sponsors: %1\n").arg(count);
    response += QString("• Combined Capacity: $%1\n").arg(totalCapacity, 0, 'f', 2);
    response += QString("• Average Capacity: $%1").arg(averageCapacity, 0, 'f', 2);

    return response;
}

QString Chatbot::getAdvancedSponsorStatistics(const QString &query) {
    QString lowercaseQuery = query.toLower();

    // Check if it's a specific statistics request
    if (lowercaseQuery.contains("how many") || lowercaseQuery.contains("number of") ||
        lowercaseQuery.contains("total sponsors")) {
        return getSponsorCountStatistics();
    }

    if (lowercaseQuery.contains("average capacity") || lowercaseQuery.contains("mean capacity")) {
        return getAverageCapacityStatistics();
    }

    if (lowercaseQuery.contains("highest capacity") || lowercaseQuery.contains("top sponsor")) {
        return getTopSponsorsByCapacity(1); // Just the top one
    }

    if (lowercaseQuery.contains("domain distribution") || lowercaseQuery.contains("by domain")) {
        return getDomainDistributionStatistics();
    }

    if (lowercaseQuery.contains("capacity range") || lowercaseQuery.contains("capacity distribution")) {
        return getCapacityRangeStatistics();
    }

    // Default comprehensive statistics
    return getComprehensiveSponsorStatistics();
}

QString Chatbot::getComprehensiveSponsorStatistics() {
    QSqlQuery query(db);
    QString response = "📊 Comprehensive Sponsor Statistics\n\n";

    // Total sponsors
    if (query.exec("SELECT COUNT(*) FROM SPONSOR")) {
        if (query.next()) {
            int count = query.value(0).toInt();
            response += QString("🔹 Total Sponsors: %1\n").arg(count);
        }
    }

    // Total and average capacity
    if (query.exec("SELECT SUM(CAPACITE_FINANCIERE), AVG(CAPACITE_FINANCIERE) FROM SPONSOR")) {
        if (query.next()) {
            double totalCapacity = query.value(0).toDouble();
            double avgCapacity = query.value(1).toDouble();
            response += QString("🔹 Total Financial Capacity: $%1\n").arg(totalCapacity, 0, 'f', 2);
            response += QString("🔹 Average Capacity: $%1\n").arg(avgCapacity, 0, 'f', 2);
        }
    }

    // Min and max capacity
    if (query.exec("SELECT MIN(CAPACITE_FINANCIERE), MAX(CAPACITE_FINANCIERE) FROM SPONSOR")) {
        if (query.next()) {
            double minCapacity = query.value(0).toDouble();
            double maxCapacity = query.value(1).toDouble();
            response += QString("🔹 Minimum Capacity: $%1\n").arg(minCapacity, 0, 'f', 2);
            response += QString("🔹 Maximum Capacity: $%1\n").arg(maxCapacity, 0, 'f', 2);
        }
    }

    response += "\n";

    // Domain breakdown
    if (query.exec("SELECT DOMAINE, COUNT(*), SUM(CAPACITE_FINANCIERE), "
                   "AVG(CAPACITE_FINANCIERE) FROM SPONSOR GROUP BY DOMAINE ORDER BY COUNT(*) DESC")) {
        response += "🏷️ Domain Breakdown:\n";
        while (query.next()) {
            QString domain = query.value(0).toString();
            int count = query.value(1).toInt();
            double domainCapacity = query.value(2).toDouble();
            double avgDomainCapacity = query.value(3).toDouble();

            response += QString("  • %1: %2 sponsors ($%3 total, $%4 avg)\n")
                            .arg(domain)
                            .arg(count)
                            .arg(domainCapacity, 0, 'f', 2)
                            .arg(avgDomainCapacity, 0, 'f', 2);
        }
        response += "\n";
    }

    // Top 5 sponsors
    response += getTopSponsorsByCapacity(5);

    // Capacity distribution
    response += "\n💰 Capacity Distribution:\n";
    QVector<QPair<QString, double>> ranges = {
        {"Under $10k", 10000},
        {"$10k-$50k", 50000},
        {"$50k-$100k", 100000},
        {"$100k-$500k", 500000},
        {"Over $500k", 0}
    };

    for (int i = 0; i < ranges.size(); i++) {
        QString condition;
        if (i == 0) {
            condition = "CAPACITE_FINANCIERE < " + QString::number(ranges[i].second);
        } else if (i == ranges.size() - 1) {
            condition = "CAPACITE_FINANCIERE >= " + QString::number(ranges[i-1].second);
        } else {
            condition = "CAPACITE_FINANCIERE >= " + QString::number(ranges[i-1].second) +
                        " AND CAPACITE_FINANCIERE < " + QString::number(ranges[i].second);
        }

        if (query.exec("SELECT COUNT(*) FROM SPONSOR WHERE " + condition)) {
            if (query.next()) {
                int count = query.value(0).toInt();
                response += QString("  • %1: %2 sponsors\n").arg(ranges[i].first).arg(count);
            }
        }
    }

    return response;
}

QString Chatbot::getSponsorCountStatistics() {
    QSqlQuery query(db);
    if (!query.exec("SELECT COUNT(*) FROM SPONSOR")) {
        return "Error retrieving sponsor count: " + query.lastError().text();
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        return QString("There are currently %1 sponsors in the database.").arg(count);
    }

    return "No sponsor count information available.";
}

QString Chatbot::getAverageCapacityStatistics() {
    QSqlQuery query(db);
    if (!query.exec("SELECT AVG(CAPACITE_FINANCIERE) FROM SPONSOR")) {
        return "Error retrieving average capacity: " + query.lastError().text();
    }

    if (query.next()) {
        double avgCapacity = query.value(0).toDouble();
        return QString("The average financial capacity of sponsors is $%1.")
            .arg(avgCapacity, 0, 'f', 2);
    }

    return "No average capacity information available.";
}

QString Chatbot::getDomainDistributionStatistics() {
    QSqlQuery query(db);
    if (!query.exec("SELECT DOMAINE, COUNT(*) FROM SPONSOR GROUP BY DOMAINE ORDER BY COUNT(*) DESC")) {
        return "Error retrieving domain distribution: " + query.lastError().text();
    }

    QString response = "🏷️ Sponsor Domain Distribution:\n";
    int total = 0;

    while (query.next()) {
        QString domain = query.value(0).toString();
        int count = query.value(1).toInt();
        total += count;

        response += QString("• %1: %2 sponsors\n").arg(domain).arg(count);
    }

    if (total == 0) {
        return "No domain distribution information available.";
    }

    response += QString("\nTotal sponsors: %1").arg(total);
    return response;
}

QString Chatbot::getCapacityRangeStatistics() {
    QSqlQuery query(db);
    QString response = "💰 Sponsor Capacity Ranges:\n";

    QVector<QPair<QString, QString>> ranges = {
        {"Under $10k", "CAPACITE_FINANCIERE < 10000"},
        {"$10k-$50k", "CAPACITE_FINANCIERE >= 10000 AND CAPACITE_FINANCIERE < 50000"},
        {"$50k-$100k", "CAPACITE_FINANCIERE >= 50000 AND CAPACITE_FINANCIERE < 100000"},
        {"$100k-$500k", "CAPACITE_FINANCIERE >= 100000 AND CAPACITE_FINANCIERE < 500000"},
        {"Over $500k", "CAPACITE_FINANCIERE >= 500000"}
    };

    for (const auto &range : ranges) {
        if (query.exec("SELECT COUNT(*) FROM SPONSOR WHERE " + range.second)) {
            if (query.next()) {
                int count = query.value(0).toInt();
                response += QString("• %1: %2 sponsors\n").arg(range.first).arg(count);
            }
        }
    }

    return response;
}
QVector<int> Chatbot::recommendProjectsWithFilters(const QString &domain, double budgetLimit)
{
    QVector<int> recommendedIds;
    QSqlQuery query(db);

    QString queryStr = "SELECT ID_PROJET FROM PROJET WHERE 1=1";

    if (!domain.isEmpty()) {
        queryStr += " AND DOMAINE = :domain";
    }

    if (budgetLimit > 0) {
        queryStr += " AND BUDGET_REQUIS <= :budget";
    }

    queryStr += " ORDER BY BUDGET_REQUIS ASC LIMIT 5";

    query.prepare(queryStr);

    if (!domain.isEmpty()) {
        query.bindValue(":domain", domain);
    }

    if (budgetLimit > 0) {
        query.bindValue(":budget", budgetLimit);
    }

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return recommendedIds;
    }

    while (query.next()) {
        recommendedIds.append(query.value(0).toInt());
    }

    return recommendedIds;
}

QString Chatbot::getFilteredProjectInfo(int projectId)
{
    QSqlQuery query(db);
    query.prepare("SELECT NOM_PROJET, PROBLEME_RESOLU, BUDGET_REQUIS, DOMAINE FROM PROJET WHERE ID_PROJET = :id");
    query.bindValue(":id", projectId);

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return "Project information not available.";
    }

    if (query.next()) {
        QString name = query.value(0).toString();
        QString problem = query.value(1).toString();
        double budget = query.value(2).toDouble();
        QString domain = query.value(3).toString();

        return QString("📌 Project: %1\n"
                       "🔹 Solves: %2\n"
                       "💰 Budget: $%3\n"
                       "🏷️ Domain: %4")
            .arg(name)
            .arg(problem)
            .arg(budget, 0, 'f', 2)
            .arg(domain);
    }

    return QString("Project information not available for ID: %1").arg(projectId);
}

QString Chatbot::getDetailedProjectInfo(int projectId)
{
    QSqlQuery query(db);
    query.prepare("SELECT NOM_PROJET, PROBLEME_RESOLU, PUBLIC_CIBLE, PROPOSITION_DE_VALEUR, "
                  "ANALYSE_DU_MARCHE, BUDGET_REQUIS, CONTRAINTES, DOMAINE, CONCURRENCE "
                  "FROM PROJET WHERE ID_PROJET = :id");
    query.bindValue(":id", projectId);

    if (!query.exec() || !query.next()) {
        return "Sorry, I couldn't find detailed information for that project.";
    }

    QString name = query.value(0).toString();
    QString problem = query.value(1).toString();
    QString audience = query.value(2).toString();
    QString valueProp = query.value(3).toString();
    QString market = query.value(4).toString();
    double budget = query.value(5).toDouble();
    QString constraints = query.value(6).toString();
    QString domain = query.value(7).toString();
    QString competition = query.value(8).toString();

    QString response = QString("📋 %1 (Project ID: %2)\n\n").arg(name).arg(projectId);
    response += QString("🏷️ Domain: %1\n\n").arg(domain);
    response += QString("🔍 Problem Solved:\n%1\n\n").arg(problem);
    response += QString("👥 Target Audience:\n%1\n\n").arg(audience);
    response += QString("💎 Value Proposition:\n%1\n\n").arg(valueProp);
    response += QString("📊 Market Analysis:\n%1\n\n").arg(market);
    response += QString("💰 Required Budget: $%1\n\n").arg(budget, 0, 'f', 2);
    response += QString("⚠️ Constraints:\n%1\n\n").arg(constraints);
    response += QString("🏆 Competition:\n%1\n\n").arg(competition);

    // Find potential sponsors
    response += "🤝 Potential Sponsors:\n";

    QSqlQuery sponsorQuery(db);
    sponsorQuery.prepare("SELECT NOM, CODE_FISCAL, CAPACITE_FINANCIERE FROM SPONSOR "
                         "WHERE DOMAINE = :domain AND CAPACITE_FINANCIERE >= :budget "
                         "ORDER BY CAPACITE_FINANCIERE DESC LIMIT 3");
    sponsorQuery.bindValue(":domain", domain);
    sponsorQuery.bindValue(":budget", budget);

    if (sponsorQuery.exec()) {
        bool foundSponsors = false;

        while (sponsorQuery.next()) {
            foundSponsors = true;
            QString sponsorName = sponsorQuery.value(0).toString();
            QString sponsorCode = sponsorQuery.value(1).toString();
            double capacity = sponsorQuery.value(2).toDouble();

            response += QString("- %1 (Code: %2, Capacity: $%3)\n")
                            .arg(sponsorName, sponsorCode)
                            .arg(capacity, 0, 'f', 2);
        }

        if (!foundSponsors) {
            response += "No matching sponsors found for this project's domain and budget.\n";
        }
    }

    response += "\nWould you like to proceed with this project or continue exploring others?";

    return response;
}
QVector<int> Chatbot::recommendProjects()
{
    QStringList problemTokens = tokenizeInput(userCriteria["problem"]);
    QStringList audienceTokens = tokenizeInput(userCriteria["audience"]);
    QStringList valuePropTokens = tokenizeInput(userCriteria["value_prop"]);
    QStringList marketTokens = tokenizeInput(userCriteria["market"]);
    QStringList competitionTokens = tokenizeInput(userCriteria["competition"]);

    QMap<int, double> relevanceMap = calculateProjectRelevance(
        problemTokens, audienceTokens, valuePropTokens, marketTokens, competitionTokens);

    // Sort projects by relevance score
    QVector<QPair<int, double>> sortedProjects;
    for (auto it = relevanceMap.begin(); it != relevanceMap.end(); ++it) {
        sortedProjects.append(qMakePair(it.key(), it.value()));
    }

    std::sort(sortedProjects.begin(), sortedProjects.end(),
              [](const QPair<int, double> &a, const QPair<int, double> &b) {
                  return a.second > b.second;
              });

    // Get only the most relevant project (top score)
    QVector<int> recommendedIds;
    if (!sortedProjects.isEmpty() && sortedProjects.first().second > 0) {
        recommendedIds.append(sortedProjects.first().first);
    }

    // If no matches found, return an empty vector
    return recommendedIds;
}

QMap<int, double> Chatbot::calculateProjectRelevance(
    const QStringList &problemTokens,
    const QStringList &audienceTokens,
    const QStringList &valuePropTokens,
    const QStringList &marketTokens,
    const QStringList &competitionTokens)
{
    QMap<int, double> relevanceMap;
    QSqlQuery query(db);

    if (!query.exec("SELECT ID_PROJET, PROBLEME_RESOLU, PUBLIC_CIBLE, PROPOSITION_DE_VALEUR, ANALYSE_DU_MARCHE, CONCURRENCE FROM PROJET")) {
        qDebug() << "Query failed:" << query.lastError().text();
        return relevanceMap;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString problem = query.value(1).toString().toLower();
        QString audience = query.value(2).toString().toLower();
        QString valueProp = query.value(3).toString().toLower();
        QString market = query.value(4).toString().toLower();
        QString competition = query.value(5).toString().toLower();

        double problemScore = calculateMatchScore(problemTokens, problem);
        double audienceScore = calculateMatchScore(audienceTokens, audience);
        double valuePropScore = calculateMatchScore(valuePropTokens, valueProp);
        double marketScore = calculateMatchScore(marketTokens, market);
        double competitionScore = calculateMatchScore(competitionTokens, competition);

        // Weighted score with problem being most important
        double score = problemScore * 2.0 + audienceScore * 1.5 + valuePropScore * 1.2 + marketScore * 0.8 + competitionScore * 0.5;

        if (score > 0) {
            relevanceMap[id] = score;
        }
    }

    // If no matches, return some default projects
    if (relevanceMap.isEmpty()) {
        QSqlQuery defaultQuery(db);
        if (defaultQuery.exec("SELECT ID_PROJET FROM PROJET LIMIT 3")) {
            while (defaultQuery.next()) {
                relevanceMap[defaultQuery.value(0).toInt()] = 0.1; // Small score for defaults
            }
        }
    }

    return relevanceMap;
}

QMap<int, double> Chatbot::calculateProjectRelevance(
    const QStringList &problemTokens,
    const QStringList &audienceTokens,
    const QStringList &marketTokens,
    const QStringList &competitionTokens)
{
    QMap<int, double> relevanceMap;
    QSqlQuery query(db);

    if (!query.exec("SELECT ID_PROJET, PROBLEME_RESOLU, PUBLIC_CIBLE, ANALYSE_DU_MARCHE, CONCURRENCE FROM PROJET")) {
        qDebug() << "Query failed:" << query.lastError().text();
        return relevanceMap;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString problem = query.value(1).toString().toLower();
        QString audience = query.value(2).toString().toLower();
        QString market = query.value(3).toString().toLower();
        QString competition = query.value(4).toString().toLower();

        double problemScore = calculateMatchScore(problemTokens, problem);
        double audienceScore = calculateMatchScore(audienceTokens, audience);
        double marketScore = calculateMatchScore(marketTokens, market);
        double competitionScore = calculateMatchScore(competitionTokens, competition);

        // Weighted score with problem being most important
        double score = problemScore * 2.0 + audienceScore * 1.5 + marketScore * 0.8 + competitionScore * 0.5;

        if (score > 0) {
            relevanceMap[id] = score;
        }
    }

    return relevanceMap;
}

double Chatbot::calculateMatchScore(const QStringList &tokens, const QString &text)
{
    if (tokens.isEmpty() || text.isEmpty()) return 0.0;

    double score = 0;
    QString lowercaseText = text.toLower();

    foreach (const QString &token, tokens) {
        if (token.length() < 3) continue;

        // Exact match gives higher score
        if (lowercaseText.contains(token.toLower())) {
            score += 2.0;
        }
        // Partial match gives lower score
        else {
            QRegularExpression regex("\\b" + token + "\\w*", QRegularExpression::CaseInsensitiveOption);
            if (regex.match(lowercaseText).hasMatch()) {
                score += 1.0;
            }
        }
    }

    return score;
}

QString Chatbot::getProjectInfo(int projectId)
{
    QSqlQuery query(db);
    query.prepare("SELECT NOM_PROJET, PROBLEME_RESOLU, PUBLIC_CIBLE, PROPOSITION_DE_VALEUR, BUDGET_REQUIS, DOMAINE FROM PROJET WHERE ID_PROJET = :id");
    query.bindValue(":id", projectId);

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return QString("Project information not available for ID: %1").arg(projectId);
    }

    if (query.next()) {
        QString name = query.value(0).toString();
        QString problem = query.value(1).toString();
        QString audience = query.value(2).toString();
        QString valueProp = query.value(3).toString();
        double budget = query.value(4).toDouble();
        QString domain = query.value(5).toString();

        return QString("📌 Project: %1 (ID: %2)\n"
                       "🔹 Problem Solved: %3\n"
                       "👥 Target Audience: %4\n"
                       "💎 Value Proposition: %5\n"
                       "💰 Budget: $%6\n"
                       "🏷️ Domain: %7")
            .arg(name)
            .arg(projectId)
            .arg(problem)
            .arg(audience)
            .arg(valueProp)
            .arg(budget, 0, 'f', 2)
            .arg(domain);
    }

    return QString("Project information not available for ID: %1").arg(projectId);
}

Chatbot::ChatState Chatbot::getCurrentState() const
{
    return currentState;
}

void Chatbot::resetConversation()
{
    currentState = GREETING;
    userCriteria.clear();
}
QString Chatbot::handleFilteredProjectRecommendation(const QString &query)
{
    // Extract budget constraint with more variations
    double budgetLimit = -1;
    QRegularExpression budgetRegex("(under|less than|below|up to|maximum|at most)\\s*\\$?(\\d+(?:[\\.,]\\d+)?)(k|kay| thousand| million)?",
                                   QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch budgetMatch = budgetRegex.match(query);

    if (budgetMatch.hasMatch()) {
        budgetLimit = budgetMatch.captured(2).replace(",", "").toDouble();
        QString unit = budgetMatch.captured(3).toLower();
        if (unit.contains("k") || unit.contains("kay") || unit.contains(" thousand")) {
            budgetLimit *= 1000;
        } else if (unit.contains(" million")) {
            budgetLimit *= 1000000;
        }
    }

    // Extract domain filter with more variations
    QString domainFilter = "";
    static const QMap<QString, QString> domainMap = {
        {"tech", "Technology"},
        {"technology", "Technology"},
        {"health", "Health"},
        {"medical", "Health"},
        {"education", "Education"},
        {"school", "Education"},
        {"finance", "Finance"},
        {"financial", "Finance"},
        {"retail", "Retail & E-commerce"},
        {"ecommerce", "Retail & E-commerce"},
        {"media", "Media & Entertainment"},
        {"entertainment", "Media & Entertainment"},
        {"automotive", "Automotive"},
        {"food", "Food"},
        {"real estate", "Real Estate"},
        {"other", "Other"}
    };

    for (auto it = domainMap.constBegin(); it != domainMap.constEnd(); ++it) {
        if (query.contains(it.key(), Qt::CaseInsensitive)) {
            domainFilter = it.value();
            break;
        }
    }

    QVector<int> recommended = recommendProjectsWithFilters(domainFilter, budgetLimit);

    if (recommended.isEmpty()) {
        return "I couldn't find projects matching your criteria. Try:\n"
               "- Adjusting budget or domain filters\n"
               "- Using broader terms\n"
               "- Asking for general recommendations (say 'recommend a project')";
    }

    QString response = "Here are projects matching your criteria:\n\n";
    for (int projectId : recommended) {
        response += getFilteredProjectInfo(projectId);
        if (projectId != recommended.last()) {
            response += "\n──────────\n";
        }
    }

    // Add filter summary
    response += "\n\n🔎 Matching criteria: ";
    QStringList criteria;
    if (budgetLimit > 0) {
        criteria << QString("budget ≤ $%1").arg(budgetLimit, 0, 'f', 2);
    }
    if (!domainFilter.isEmpty()) {
        criteria << QString("domain: %1").arg(domainFilter);
    }

    if (criteria.isEmpty()) {
        response += "all projects";
    } else {
        response += criteria.join(" and ");
    }

    response += "\n\nWould you like to:\n"
                "1. Get more details about a specific project? (say 'tell me more about project X')\n"
                "2. Refine your search with different filters\n"
                "3. See sponsor information for these projects";

    return response;
}



