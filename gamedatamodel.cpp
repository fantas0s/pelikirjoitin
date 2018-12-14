#include "gamedatamodel.h"

#define FIXED_NUM_ITEMS  3

GameDataModel::GameDataModel()
{
    m_database = qobject_cast<GameDataBase*>(GameDataBase::gamedatabaseProvider(nullptr, nullptr));
    connect(m_database, &GameDataBase::titleModified, this, &GameDataModel::titleModified);
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

void GameDataModel::titleModified(quint32 id, QString title)
{
    Q_UNUSED(title);
    int idx = m_database->getIndexOf(id);
    if ((idx >=0) &&
        (idx < m_database->numOfPlaces())) {
        dataChanged(index(idx, 0), index(idx,0), QVector<int>() << PlaceTitleRole);
    }
}
