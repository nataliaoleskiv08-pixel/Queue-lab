#pragma once
#include "Queue.h"
#include <sstream>

namespace Project1 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    private:
        ::Queue* q1;
        ::Queue* q2;
        ::Queue* qMerged;

    public:
        MyForm(void)
        {
            InitializeComponent();
            q1 = new ::Queue();
            q2 = new ::Queue();
            qMerged = nullptr;
        }

    protected:
        ~MyForm()
        {
            if (components) {
                delete components;
            }
            if (q1) { delete q1; q1 = nullptr; }
            if (q2) { delete q2; q2 = nullptr; }
            if (qMerged) { delete qMerged; qMerged = nullptr; }
        }

    private: System::Windows::Forms::TextBox^ txtQ1Input;
    private: System::Windows::Forms::TextBox^ txtQ2Input;
    private: System::Windows::Forms::Button^ btnFillAndAnalyze;
    private: System::Windows::Forms::TextBox^ txtSearch;
    private: System::Windows::Forms::RichTextBox^ txtOutput;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label3;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->txtQ1Input = (gcnew System::Windows::Forms::TextBox());
            this->txtQ2Input = (gcnew System::Windows::Forms::TextBox());
            this->btnFillAndAnalyze = (gcnew System::Windows::Forms::Button());
            this->txtSearch = (gcnew System::Windows::Forms::TextBox());
            this->txtOutput = (gcnew System::Windows::Forms::RichTextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // txtQ1Input
            // 
            this->txtQ1Input->Location = System::Drawing::Point(140, 25);
            this->txtQ1Input->Name = L"txtQ1Input";
            this->txtQ1Input->Size = System::Drawing::Size(350, 22);
            this->txtQ1Input->TabIndex = 0;
            // 
            // txtQ2Input
            // 
            this->txtQ2Input->Location = System::Drawing::Point(140, 60);
            this->txtQ2Input->Name = L"txtQ2Input";
            this->txtQ2Input->Size = System::Drawing::Size(350, 22);
            this->txtQ2Input->TabIndex = 1;
            // 
            // btnFillAndAnalyze
            // 
            this->btnFillAndAnalyze->Location = System::Drawing::Point(25, 130);
            this->btnFillAndAnalyze->Name = L"btnFillAndAnalyze";
            this->btnFillAndAnalyze->Size = System::Drawing::Size(465, 30);
            this->btnFillAndAnalyze->TabIndex = 2;
            this->btnFillAndAnalyze->Text = L"Заповнити черги та провести аналіз";
            this->btnFillAndAnalyze->UseVisualStyleBackColor = true;
            this->btnFillAndAnalyze->Click += gcnew System::EventHandler(this, &MyForm::btnFillAndAnalyze_Click);
            // 
            // txtSearch
            // 
            this->txtSearch->Location = System::Drawing::Point(140, 95);
            this->txtSearch->Name = L"txtSearch";
            this->txtSearch->Size = System::Drawing::Size(350, 22);
            this->txtSearch->TabIndex = 3;
            // 
            // txtOutput
            // 
            this->txtOutput->Location = System::Drawing::Point(25, 175);
            this->txtOutput->Name = L"txtOutput";
            this->txtOutput->Size = System::Drawing::Size(465, 230);
            this->txtOutput->TabIndex = 4;
            this->txtOutput->Text = L"";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(22, 28);
            this->label1->Name = L"label1";
            this->label1->Size =  System::Drawing::Size(63, 16);
            this->label1->Text = L"Черга 1:";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(22, 63);
            this->label2->Name = L"label2";
            this->label2->Size =  System::Drawing::Size(63, 16);
            this->label2->Text = L"Черга 2:";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(22, 98);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(112, 16);
            this->label3->Text = L"Шукане значення:";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(515, 425);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->txtOutput);
            this->Controls->Add(this->txtSearch);
            this->Controls->Add(this->btnFillAndAnalyze);
            this->Controls->Add(this->txtQ2Input);
            this->Controls->Add(this->txtQ1Input);
            this->Name = L"MyForm";
            this->Text = L"Аналіз черги дійсних чисел";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

        System::String^ queueToString(::Queue* q) {
            System::String^ result = "";
            for (int i = 0; i < q->getCount(); i++) {
                result += q->getElementAtDirect(i).ToString() + " ";
            }
            return result;
        }

        // Допоміжна функція для заповнення черги з рядка через пробіл
        void parseAndFillQueue(System::String^ inputStr, ::Queue* queue) {
            // Очищуємо стару чергу перед новим заповненням
            while (!queue->isEmpty()) {
                queue->pop();
            }

            // Перетворюємо managed System::String в стандартний std::string
            array<Char>^ chars = inputStr->ToCharArray();
            pin_ptr<Char> pinnedChars = &chars[0];
            std::wstring wstr(pinnedChars, chars->Length);
            std::string str(wstr.begin(), wstr.end());

            std::stringstream ss(str);
            double val;
            while (ss >> val) {
                queue->pushUnique(val);
            }
        }

    private: System::Void btnFillAndAnalyze_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            // Зчитуємо дані з полів та заповнюємо черги
            parseAndFillQueue(txtQ1Input->Text, q1);
            parseAndFillQueue(txtQ2Input->Text, q2);

            txtOutput->Clear();
            txtOutput->AppendText(L"=== АНАЛІЗ ЧЕРГИ 1 ===\r\n");
            txtOutput->AppendText(L"Елементи: " + queueToString(q1) + L"\r\n");
            txtOutput->AppendText(L"Кількість елементів: " + q1->getCount().ToString() + L"\r\n");

            if (q1->getCount() > 0) {
                double minV, maxV;
                q1->getMinMax(minV, maxV);
                txtOutput->AppendText(L"Мінімальний елемент: " + minV.ToString() + L"\r\n");
                txtOutput->AppendText(L"Максимальний елемент: " + maxV.ToString() + L"\r\n");

                double val3, val2End;
                if (q1->getAt(2, val3))
                    txtOutput->AppendText(L"3-й елемент з початку: " + val3.ToString() + L"\r\n");
                else
                    txtOutput->AppendText(L"3-й елемент з початку: недостатньо елементів\r\n");

                if (q1->getAt(q1->getCount() - 2, val2End))
                    txtOutput->AppendText(L"2-й елемент з кінця: " + val2End.ToString() + L"\r\n");
                else
                    txtOutput->AppendText(L"2-й елемент з кінця: недостатньо елементів\r\n");

                double beforeMin, afterMax;
                bool hasBefore, hasAfter;
                q1->getNeighbors(beforeMin, afterMax, hasBefore, hasAfter);
                if (hasBefore) txtOutput->AppendText(L"Елемент перед мін: " + beforeMin.ToString() + L"\r\n");
                else txtOutput->AppendText(L"Елемент перед мін: відсутній\r\n");

                if (hasAfter) txtOutput->AppendText(L"Елемент після макс: " + afterMax.ToString() + L"\r\n");
                else txtOutput->AppendText(L"Елемент після макс: відсутній\r\n");
            }

            // Пошук позиції елемента за значенням
            try {
                if (!String::IsNullOrEmpty(txtSearch->Text)) {
                    double searchVal = Convert::ToDouble(txtSearch->Text);
                    int pos = q1->findPosition(searchVal);
                    if (pos != -1)
                        txtOutput->AppendText(L"Позиція шуканого елемента в Черзі 1: " + pos.ToString() + L"\r\n");
                    else
                        txtOutput->AppendText(L"Шуканий елемент не знайдено в Черзі 1.\r\n");
                }
            }
            catch (...) {}

            // Об'єднання структури
            txtOutput->AppendText(L"\r\n=== ОБ'ЄДНАННЯ ЧЕРГ ===\r\n");
            if (qMerged) delete qMerged;
            qMerged = ::Queue::merge(*q1, *q2);
            txtOutput->AppendText(L"Об'єднана черга (без повторів): " + queueToString(qMerged) + L"\r\n");
            txtOutput->AppendText(L"Кількість в об'єднаній черзі: " + qMerged->getCount().ToString() + L"\r\n");

        }
        catch (...) {
            MessageBox::Show(L"Перевірте правильність введення чисел!", L"Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    };
}