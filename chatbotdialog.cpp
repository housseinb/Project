// Add necessary includes at the top
#include "chatbotdialog.h"
#include <QMessageBox>
#include <QScrollBar>
#include <QTime>
#include <QMenu>
#include <QAction>
#include <QTimer>  // Missing include for QTimer
#include <QLabel>  // Missing include for QLabel
#include <QListWidget>  // Missing include for QListWidget
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocumentFragment>

ChatBotDialog::ChatBotDialog(QWidget *parent) : QDialog(parent), chatBot(new ChatBot(this)) {
    setupUI();
    // Initialize suggestions
    suggestions << "List all sponsors" << "Who is the best sponsor?" << "Show me sponsors in technology"
                << "Find sponsors with capacity above 100000" << "Contact information for [sponsor name]"
                << "Find sponsor with code [enter code]";

    // Load avatars
    botAvatar = QPixmap(":/images/bot_avatar.png");
    if (botAvatar.isNull()) {
        // Fallback if image is not available
        botAvatar = QPixmap(32, 32);
        botAvatar.fill(Qt::blue);
    }

    userAvatar = QPixmap(":/images/user_avatar.png");
    if (userAvatar.isNull()) {
        // Fallback if image is not available
        userAvatar = QPixmap(32, 32);
        userAvatar.fill(Qt::green);
    }

    // Welcome message
    QTimer::singleShot(300, this, [this]() {
        addBotMessage("Hello! I'm your Sponsor Assistant. How can I help you today?");
        addBotMessage("You can ask me about sponsors, their domains, financial capacities, and contact information.");
    });
}

ChatBotDialog::~ChatBotDialog() {
    delete chatBot;
}

void ChatBotDialog::setupUI() {
    // Set window properties
    setWindowTitle("Sponsor Assistant");
    setMinimumSize(500, 600);

    // Create main layout
    mainLayout = new QVBoxLayout(this);

    // Create chat display
    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);
    chatDisplay->setStyleSheet(
        "QTextEdit {"
        " background-color: #f5f5f5;"
        " border: 1px solid #cccccc;"
        " border-radius: 5px;"
        " padding: 5px;"
        " font-family: Arial, sans-serif;"
        " font-size: 12pt;"
        "}"
        );
    mainLayout->addWidget(chatDisplay);

    // Create input area layout
    QHBoxLayout *inputLayout = new QHBoxLayout();

    // Create user input field
    userInput = new QLineEdit(this);
    userInput->setPlaceholderText("Type your message here...");
    userInput->setStyleSheet(
        "QLineEdit {"
        " border: 1px solid #cccccc;"
        " border-radius: 5px;"
        " padding: 8px;"
        " font-size: 12pt;"
        "}"
        );
    inputLayout->addWidget(userInput);

    // Create send button
    sendButton = new QPushButton("Send", this);
    sendButton->setStyleSheet(
        "QPushButton {"
        " background-color: #4a86e8;"
        " color: white;"
        " border: none;"
        " border-radius: 5px;"
        " padding: 8px 15px;"
        " font-weight: bold;"
        "}"
        "QPushButton:hover {"
        " background-color: #3a76d8;"
        "}"
        "QPushButton:pressed {"
        " background-color: #2a66c8;"
        "}"
        );
    inputLayout->addWidget(sendButton);

    mainLayout->addLayout(inputLayout);

    // Create suggestion area
    QWidget *suggestionArea = new QWidget(this);
    QVBoxLayout *suggestionLayout = new QVBoxLayout(suggestionArea);
    suggestionLayout->setSpacing(5);
    suggestionLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *suggestionLabel = new QLabel("Suggestions:", this);
    suggestionLabel->setStyleSheet("font-weight: bold; margin-top: 10px;");
    suggestionLayout->addWidget(suggestionLabel);

    suggestionBox = new QListWidget(this);
    suggestionBox->setStyleSheet(
        "QListWidget {"
        " border: 1px solid #dddddd;"
        " border-radius: 5px;"
        " background-color: #ffffff;"
        "}"
        "QListWidget::item {"
        " padding: 5px;"
        " border-bottom: 1px solid #eeeeee;"
        "}"
        "QListWidget::item:hover {"
        " background-color: #e9f0ff;"
        "}"
        );
    suggestionBox->setMaximumHeight(150);

    // Populate suggestions
    for (const QString &suggestion : suggestions) {
        suggestionBox->addItem(suggestion);
    }

    suggestionLayout->addWidget(suggestionBox);
    mainLayout->addWidget(suggestionArea);

    // Set up context menu for chat display
    chatDisplay->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(chatDisplay, &QTextEdit::customContextMenuRequested, this, &ChatBotDialog::showContextMenu);

    // Connect signals and slots
    connect(userInput, &QLineEdit::returnPressed, this, &ChatBotDialog::processUserInput);
    connect(sendButton, &QPushButton::clicked, this, &ChatBotDialog::processUserInput);
    connect(suggestionBox, &QListWidget::itemClicked, this, &ChatBotDialog::useSuggestion);
}

void ChatBotDialog::processUserInput() {
    QString message = userInput->text().trimmed();
    if (message.isEmpty()) {
        return;
    }

    // Add user message to chat
    addUserMessage(message);

    // Clear input field
    userInput->clear();

    // Process message with the chatbot
    QString response = chatBot->getResponse(message);  // Changed from processMessage to getResponse

    // Add bot response with a small delay to seem more natural
    QTimer::singleShot(500, this, [this, response]() {
        addBotMessage(response);
    });
}

void ChatBotDialog::addUserMessage(const QString &message) {
    QTextCursor cursor(chatDisplay->document());
    cursor.movePosition(QTextCursor::End);

    // Create message layout
    cursor.insertBlock();
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(blockFormat);

    // Insert user avatar
    QTextImageFormat imageFormat;
    imageFormat.setWidth(32);
    imageFormat.setHeight(32);
    imageFormat.setName(":/images/user_avatar.png");
    cursor.insertImage(imageFormat);
    cursor.insertText(" ");

    // Insert user message with formatting
    QTextCharFormat charFormat;
    charFormat.setBackground(QBrush(QColor("#e3f2fd")));
    charFormat.setForeground(QBrush(QColor("#000000")));
    cursor.insertText(message, charFormat);

    // Insert timestamp
    cursor.insertBlock();
    QTextCharFormat timeFormat;
    timeFormat.setFontItalic(true);
    timeFormat.setFontPointSize(8);
    timeFormat.setForeground(QBrush(QColor("#888888")));
    cursor.insertText(QTime::currentTime().toString("hh:mm"), timeFormat);

    // Scroll to bottom
    chatDisplay->verticalScrollBar()->setValue(chatDisplay->verticalScrollBar()->maximum());
}

void ChatBotDialog::addBotMessage(const QString &message) {
    QTextCursor cursor(chatDisplay->document());
    cursor.movePosition(QTextCursor::End);

    // Create message layout
    cursor.insertBlock();
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(blockFormat);

    // Insert bot avatar
    QTextImageFormat imageFormat;
    imageFormat.setWidth(32);
    imageFormat.setHeight(32);
    imageFormat.setName(":/images/bot_avatar.png");
    cursor.insertImage(imageFormat);
    cursor.insertText(" ");

    // Insert bot message with formatting
    QTextCharFormat charFormat;
    charFormat.setBackground(QBrush(QColor("#f5f5f5")));
    charFormat.setForeground(QBrush(QColor("#000000")));
    cursor.insertText(message, charFormat);

    // Insert timestamp
    cursor.insertBlock();
    QTextCharFormat timeFormat;
    timeFormat.setFontItalic(true);
    timeFormat.setFontPointSize(8);
    timeFormat.setForeground(QBrush(QColor("#888888")));
    cursor.insertText(QTime::currentTime().toString("hh:mm"), timeFormat);

    // Scroll to bottom
    chatDisplay->verticalScrollBar()->setValue(chatDisplay->verticalScrollBar()->maximum());
}

void ChatBotDialog::useSuggestion(QListWidgetItem *item) {
    userInput->setText(item->text());
    processUserInput();
}

void ChatBotDialog::showContextMenu(const QPoint &pos) {
    QMenu *menu = new QMenu(this);

    QAction *copyAction = new QAction("Copy", this);
    connect(copyAction, &QAction::triggered, chatDisplay, &QTextEdit::copy);
    menu->addAction(copyAction);

    QAction *clearAction = new QAction("Clear Chat", this);
    connect(clearAction, &QAction::triggered, this, [this]() {
        if (QMessageBox::question(this, "Clear Chat",
                                  "Are you sure you want to clear the chat history?",
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            chatDisplay->clear();
            addBotMessage("Chat history has been cleared. How can I help you?");
        }
    });
    menu->addAction(clearAction);

    menu->exec(chatDisplay->mapToGlobal(pos));
    delete menu;
}
