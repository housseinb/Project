#ifndef CHATBOT_H
#define CHATBOT_H



#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QSqlQuery>
#include <QRegularExpression>
#include "sponsor.h"

class ChatBot : public QObject
{
    Q_OBJECT

public:
    explicit ChatBot(QObject *parent = nullptr);
     QString getResponse(const QString &message);
    ~ChatBot();

    // Process user input and generate a response
    QString processInput(const QString &input);

private:
    // Intent recognition
    enum Intent {
        GREETING,
        FAREWELL,
        LIST_SPONSORS,
        FIND_SPONSOR_BY_NAME,
        FIND_SPONSOR_BY_CODE,
        FIND_SPONSORS_BY_DOMAIN,
        FIND_SPONSORS_BY_CAPACITY,
        BEST_SPONSOR,
        GET_CONTACT_INFO,
        UNKNOWN
    };

    // Knowledge base for responses
    QStringList greetings;
    QStringList farewells;
    QStringList unknownResponses;
    QMap<QString, QStringList> domainKeywords;
    QMap<QString, QRegularExpression> intentPatterns;

    // Methods for processing intents
    Intent recognizeIntent(const QString &input);
    QString generateResponse(Intent intent, const QString &input);

    // Database query helpers
    QList<Sponsor> getSponsors(const QString &condition = QString());
    Sponsor getSponsorByCode(const QString &code);
    Sponsor getSponsorByName(const QString &name);
    QList<Sponsor> getSponsorsByDomain(const QString &domain);
    QList<Sponsor> getSponsorsByCapacityRange(double min, double max);
    Sponsor getBestSponsor();
    QString getContactInfo(const QString &identifier);

    // Helper methods for entity extraction
    QString extractName(const QString &input);
    QString extractCode(const QString &input);
    QString extractDomain(const QString &input);
    QPair<double, double> extractCapacityRange(const QString &input);

    // Initialize response templates and patterns
    void initializeKnowledgeBase();
};


#endif // CHATBOT_H
