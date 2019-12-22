#ifndef DELEGATE_H
#define DELEGATE_H
#include <QItemDelegate>
#include <QLineEdit>
#include <QDoubleValidator>

class Delegate : public QItemDelegate
{
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        Q_UNUSED(option);
        Q_UNUSED(index);

        QLineEdit *lineEdit = new QLineEdit(parent);
        QIntValidator *validator = new QIntValidator(0, 1000000, lineEdit);
        lineEdit->setValidator(validator);
        return lineEdit;
    }
};

#endif // DELEGATE_H
