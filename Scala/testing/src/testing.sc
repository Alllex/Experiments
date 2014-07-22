

class BankAccount {
  private[this] var cash: Int = 0
  def deposit(amount: Int) { cash += amount }
  def withdraw(amount: Int) { cash -= amount }
  def balance = cash
}

object session {
  val a = new BankAccount                         //> a  : BankAccount = BankAccount@4963d86c
  a.balance                                       //> res0: Int = 0
  a.deposit(500)
  a.balance                                       //> res1: Int = 500
  a.withdraw(100)
  a.balance                                       //> res2: Int = 400
}