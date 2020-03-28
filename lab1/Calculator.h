#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<QJSEngine>

class Calculator : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentExpression READ getExpression WRITE setExpression MEMBER _currentExpression)
    Q_PROPERTY(QString currentResult READ getResult MEMBER _currentResult NOTIFY resultChanged)

    private:
        QString _currentExpression = "";
        QString _currentResult = "0";

        QVector<QPair<QString, QString>> _history;

        void _updateCurrentResult() {
            if (_currentExpression.isEmpty()) {
                // hardcoded zero if empty, without this expression will be undefined
                _currentResult = "0";
            } else {
                QJSEngine engine;
                _currentResult = engine.evaluate(getExpression()).toString();
            }

            emit resultChanged(_currentResult);
        }

    public:
        QString getExpression()
        {
            return _currentExpression;
        }

        void setExpression(QString newExpression)
        {
            _currentExpression = newExpression;
            _updateCurrentResult();
        }

        QString getResult()
        {
            return _currentResult;
        }

        virtual ~Calculator() {
            // no action needed
        }

   signals:
        void resultChanged(const QString &newText);

   public slots:
        void changeExpression(const QString &value) {
            setExpression(value);
        }

        void handleInput(const QString &value)  {
            setExpression(getExpression() + value);
        }
};


#endif // CALCULATOR_H
