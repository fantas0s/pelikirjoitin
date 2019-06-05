#ifndef GAMEDATAMODEL_H
#define GAMEDATAMODEL_H
#include <QAbstractListModel>
#include "gamedatabase.h"
class GameDataModel : public QAbstractListModel
{
public:
    enum {
        PlaceIdRole = Qt::UserRole+1,
        PlaceTitleRole = Qt::UserRole+2
    };
    GameDataModel();
    Q_INVOKABLE QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QModelIndex parent(const QModelIndex &child) const override;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
private slots:
    void titleModified(int index, QString title);
    void indexDeleted(int index);
    void indexAdded(int index);
private:
    GameDataBase* m_database;
};

#endif // GAMEDATAMODEL_H
