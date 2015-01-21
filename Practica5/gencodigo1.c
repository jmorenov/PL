int main()
{
	START_VAR	
	int n, curr;
	END_VAR

	input "introduce un numero : ", n;
	output n, " = ";
	
	curr = 2;
	while(curr<=n)
	{	
		START_VAR
			int d;
		END_VAR
		d = n/curr;
		if(d*curr == n)
		{
			output "* ", curr, " ";
			n = n/curr;
		}
		else
		{
			curr = curr + 1;
		}
	}
	output "\n";
}

