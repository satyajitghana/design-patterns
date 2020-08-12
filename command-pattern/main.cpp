#include <iostream>
#include <vector>
#include <string>

struct BankAccount
{
    int32_t m_balance;

    void deposit(int32_t amount) { m_balance += amount; }
    void withdraw(int32_t amount) { m_balance -= amount; }
};

struct Command
{
    virtual void execute() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
    enum class Action : bool
    {
        deposit,
        withdraw
    };
    BankAccount &m_ac;
    Action m_cmd;
    int32_t m_amount;

    BankAccountCommand(BankAccount &ac, Action a, int32_t amnt) : m_ac(ac), m_cmd(a), m_amount(amnt) {}

    void execute()
    {
        (m_cmd == Action::deposit) ? m_ac.deposit(m_amount) : m_ac.withdraw(m_amount);
    }

    void undo()
    {
        (m_cmd == Action::deposit) ? m_ac.withdraw(m_amount) : m_ac.deposit(m_amount);
    }
};

struct CompositeBankAccountCommand : std::vector<BankAccountCommand>, Command
{
    CompositeBankAccountCommand(const std::initializer_list<value_type> &items) : std::vector<BankAccountCommand>(items) {}

    void execute()
    {
        for (auto &cmd : *this)
            cmd.execute();
    }

    void undo()
    {
        for (auto &cmd : *this)
            cmd.undo();
    }
};

int main()
{
    BankAccount ba1{1000};
    BankAccount ba2{1200};

    CompositeBankAccountCommand commands{
        BankAccountCommand{ba1, BankAccountCommand::Action::withdraw, 200},
        BankAccountCommand{ba2, BankAccountCommand::Action::deposit, 200}};

    commands.execute();

    std::cout << ba1.m_balance << std::endl;
    std::cout << ba2.m_balance << std::endl;

    commands.undo();

    std::cout << ba1.m_balance << std::endl;
    std::cout << ba2.m_balance << std::endl;

    return EXIT_SUCCESS;
}
