#include "gamedatamodel.h"

#define FIXED_NUM_ITEMS  3

GameDataModel::GameDataModel()
{
    m_database = qobject_cast<GameDataBase*>(GameDataBase::gamedatabaseProvider(nullptr, nullptr));
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
            return m_database->id(index.row());
        case PlaceTitleRole:
            return m_database->title(m_database->id(index.row()));
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
