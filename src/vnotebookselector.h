#ifndef VNOTEBOOKSELECTOR_H
#define VNOTEBOOKSELECTOR_H

#include <QComboBox>
#include <QVector>
#include <QString>

class VNotebook;
class VNote;
class VEditArea;
class QListWidget;
class QAction;
class QListWidgetItem;

class VNotebookSelector : public QComboBox
{
    Q_OBJECT
public:
    explicit VNotebookSelector(VNote *vnote, QWidget *p_parent = 0);
    void update();
    inline void setEditArea(VEditArea *p_editArea);

signals:
    void curNotebookChanged(VNotebook *p_notebook);
    // Info of current notebook was changed.
    void notebookUpdated(const VNotebook *p_notebook);

public slots:
    bool newNotebook();
    void deleteNotebook();
    void editNotebookInfo();

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void handleCurIndexChanged(int p_index);
    void handleItemActivated(int p_index);
    void requestPopupListContextMenu(QPoint p_pos);

private:
    void initActions();
    void updateComboBox();
    VNotebook *findNotebook(const QString &p_name);
    // Return the index of @p_notebook in m_noteboks.
    int indexOfNotebook(const VNotebook *p_notebook);
    void createNotebook(const QString &p_name, const QString &p_path);
    void deleteNotebook(VNotebook *p_notebook);
    void addNotebookItem(const QString &p_name);
    // @p_index is the index of m_notebooks, NOT of QComboBox.
    void removeNotebookItem(int p_index);
    // @p_index is the index of QComboBox.
    void updateComboBoxItem(int p_index, const QString &p_name);
    void insertAddNotebookItem();
    // @p_index is the index of m_notebooks.
    void setCurrentIndexNotebook(int p_index);
    int indexOfListItem(const QListWidgetItem *p_item);
    // @p_index is the idnex of QComboBox.
    inline VNotebook *getNotebookFromComboIndex(int p_index);

    VNote *m_vnote;
    QVector<VNotebook *> &m_notebooks;
    VEditArea *m_editArea;
    QListWidget *m_listWidget;
    int m_lastValidIndex;

    // Actions
    QAction *m_deleteNotebookAct;
    QAction *m_notebookInfoAct;

    // We will add several special action item in the combobox. This is the start index
    // of the real notebook items related to m_notebooks.
    static const int c_notebookStartIdx;
};

inline void VNotebookSelector::setEditArea(VEditArea *p_editArea)
{
    m_editArea = p_editArea;
}

inline VNotebook *VNotebookSelector::getNotebookFromComboIndex(int p_index)
{
    if (p_index < c_notebookStartIdx) {
        return NULL;
    }
    int nbIdx = p_index - c_notebookStartIdx;
    if (nbIdx >= m_notebooks.size()) {
        return NULL;
    }
    return m_notebooks[nbIdx];
}

#endif // VNOTEBOOKSELECTOR_H
