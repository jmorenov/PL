int main()
{
	START_VAR
		int n, curr, ultim, cuenta, primero;
	END_VAR
	
	curr = 2;
	ultim = 0;
	cuenta = 0;
	primero = 1;
	
	input "introduce un numero : ", n;
	
	while(curr <= n)
	{
		START_VAR
			int d;
		END_VAR
		d = n/curr;
		
		if(d * curr == n)
		{
			if(curr != ultim)
			{
				ultim = curr;
				cuenta = 1;
			}
			else
			{
				cuenta = cuenta + 1;
			}
			n = n/curr;
		}
		else
		{
			if(cuenta>0)
			{
				if(primero == 0)
				{
					output " *";
				}
				primero = 0;
				output " ", curr;
				if(cuenta >1)
				{
					output " ", cuenta;
				}
				curr = curr + 1;
				cuenta = 0;
			}
		}
	}
	if(cuenta > 0)
	{
		if(primero == 0)
		{
			output " *";
		}	
		primero = 0;
		output " ", curr;
		if(cuenta >1)
		{
			output "^", cuenta;
		}
	}
	output "\n";
}
