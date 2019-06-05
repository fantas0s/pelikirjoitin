#include "gamedatamodel.h"
#include <QDebug>

#define FIXED_NUM_ITEMS  3

GameDataModel::GameDataModel()
{
    m_database = qobject_cast<GameDataBase*>(GameDataBase::gamedatabaseProvider(nullptr, nullptr));
    connect(m_database, &GameDataBase::titleModified, this, &GameDataModel::titleModified);
    connect(m_database, &GameDataBase::indexDeleted, this, &GameDataModel::indexDeleted);
    connect(m_database, &GameDataBase::indexAdded, this, &GameDataModel::indexAdded);
}

QModelIndex GameDataModel::index(int row, int column,
                          const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if( (row >= 0) &&
        (row < m_database->numOfPlaces()) &&
        (0 == column) )
        return createIndex(row, column);
    return QModelIndex();
}

QModelIndex GameDataModel::parent(const QModelIndex &child) const
{
    (void)child;
    return QModelIndex();
}

int GameDataModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return m_database->numOfPlaces();
}

QVariant GameDataModel::data(const QModelIndex &index, int role) const
{
    if( hasIndex(index.row(), index.column()) )
    {
        switch( role )
        {
        case PlaceIdRole:
            return m_database->getIdAt(index.row());
        case PlaceTitleRole:
            return m_database->getTitle(m_database->getIdAt(index.row()));
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QHash<int, QByteArray> GameDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PlaceIdRole] = "placeId";
    roles[PlaceTitleRole] = "placeTitle";
    return roles;
}

void GameDataModel::titleModified(int idx, QString title)
{
    Q_UNUSED(title);
    if ((idx >=0) &&
        (idx < m_database->numOfPlaces())) {
        emit dataChanged(index(idx, 0), index(idx,0), QVector<int>() << PlaceTitleRole);
    }
}

void GameDataModel::indexDeleted(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    endRemoveRows();
}

void GameDataModel::indexAdded(int index)
{
    beginInsertRows(QModelIndex(), index, index);
    endInsertRows();
}
