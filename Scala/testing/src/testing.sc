

class BankAccount {
  private[this] var cash: Int = 0
  def deposit(amount: Int) { cash += amount }
  def withdraw(amount: Int) { cash -= amount }
  def balance = cash
}

object session {
}