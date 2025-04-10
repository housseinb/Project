#ifndef CHATBOTDIALOG_H
#define CHATBOTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QStringList>
#include <QPixmap>
#include <QListWidget>
#include "chatbot.h"

class ChatBotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatBotDialog(QWidget *parent = nullptr);

    ~ChatBotDialog();

private slots:
    void processUserInput();
    void useSuggestion(QListWidgetItem *item);
    void showContextMenu(const QPoint &pos);

private:
    void setupUI();
    void addUserMessage(const QString &message);
    void addBotMessage(const QString &message);

    QVBoxLayout *mainLayout;
    QTextEdit *chatDisplay;
    QLineEdit *userInput;
    QPushButton *sendButton;
    QListWidget *suggestionBox;
    QStringList suggestions;
    QPixmap botAvatar;
    QPixmap userAvatar;
    ChatBot *chatBot;
};

#endif // CHATBOTDIALOG_H
