#ifndef CHOICETEMPSTOREITEM_H
#define CHOICETEMPSTOREITEM_H
#include <QStringList>

class ChoiceTempStoreItem
{
public:
    QString parentName;
    QStringList choices;
    QStringList choiceTargets;
};

#endif // CHOICETEMPSTOREITEM_H
