#ifndef CHATBOT_H
#define CHATBOT_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QPair>

class Chatbot
{
public:
    enum ChatState {
        GREETING,
        ASK_PROBLEM,
        ASK_AUDIENCE,
        ASK_VALUE_PROP,
        ASK_MARKET_ANALYSIS,  // This is the correct name in the header
        ASK_COMPETITION,
        RECOMMEND,
        SPONSOR_QUERY,
        PROJECT_FILTER
    };

    Chatbot(QSqlDatabase& database);
    ~Chatbot();

    QString processInput(const QString &userInput);
    ChatState getCurrentState() const;
    void resetConversation();

private:
    QSqlDatabase& db;
    ChatState currentState;
    QMap<QString, QString> userCriteria;
    QMap<QString, QPair<QString, ChatState>> commonResponses;
    QStringList helpResponses;

    // Initialization
    void initializeCommonResponses();

    // Input processing helpers
    QStringList tokenizeInput(const QString &input);
    bool isCommonPhrase(const QString &input);
    QString getCommonResponse(const QString &input);
    double parseFinancialAmount(const QString &amountStr);

    // Field extraction
    QString extractFieldFromQuery(const QString &query, const QStringList &fields);
    QString extractSponsorIdentifier(const QString &query);
    int extractProjectReference(const QString &input);

    // Request detection
    bool shouldStartProjectRecommendation(const QString &input);
    bool containsSponsorInfoRequest(const QString &input);
    bool isProjectRecommendationWithFilters(const QString &input);
    bool isStatisticsRequest(const QString &input);

    // Information retrieval - Projects
    QString getDetailedProjectInfo(int projectId);
    QString getFilteredProjectInfo(int projectId);
    QString getProjectInfo(int projectId);

    // Information retrieval - Sponsors
    QString getSponsorDetails(const QString &identifier, const QString &specificField = "");
    QString getAllSponsorsInfo();
    QString getTopSponsorsByCapacity(int limit = 5);
    QString getSponsorsByDomain(const QString &domain);
    QString getSponsorsByCapacity(const QString &comparison, double amount);

    // Statistics
    QString getAdvancedSponsorStatistics(const QString &query);
    QString getComprehensiveSponsorStatistics();
    QString getSponsorCountStatistics();
    QString getAverageCapacityStatistics();
    QString getDomainDistributionStatistics();
    QString getCapacityRangeStatistics();

    // Main handlers
    QString handleAdvancedSponsorQuery(const QString &query);
    QString handleFilteredProjectRecommendation(const QString &query);

    // Recommendation engines
    QVector<int> recommendProjects();
    QVector<int> recommendProjectsWithFilters(const QString &domain, double budgetLimit);
    // In chatbot.h, add this to the private section:
    QMap<int, double> calculateProjectRelevance(
        const QStringList &problemTokens,
        const QStringList &audienceTokens,
        const QStringList &marketTokens,
        const QStringList &competitionTokens);

    QMap<int, double> calculateProjectRelevance(
        const QStringList &problemTokens,
        const QStringList &audienceTokens,
        const QStringList &valuePropTokens,
        const QStringList &marketTokens,
        const QStringList &competitionTokens);
    double calculateMatchScore(const QStringList &tokens, const QString &text);
};

#endif // CHATBOT_H
