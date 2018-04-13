from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.common.by import By
from selenium import webdriver

import csv
import os
import random
import time

class BingBot(object):
	""" Initializes bot with essential data and
	which user agent will be used """
	def __init__(self, email, password, is_mobile=False):
		self.email = email
		self.password = password
		self.is_mobile = is_mobile
		
		self.explicit_wait = 3
		self.min_search_wait = 2
		self.max_search_wait = 10
		self.num_searches_to_perform = 20
		
		self.login_url = 'https://login.live.com/'
		self.bing_url = 'https://www.bing.com/'
		self.word_list = 'word_list.txt'
		
		self.profile = self.firefox_profile()
		self.driver = webdriver.Firefox(self.profile)
	
	def firefox_profile(self):
		''' This method gives the ability to switch between desktop and 
		mobile user agents '''
		profile = webdriver.FirefoxProfile()
		if self.is_mobile:
			profile.set_preference("general.useragent.override", "Mozilla/5.0 (Android 4.4; Mobile; rv:41.0) Gecko/41.0 Firefox/41.0")
		return profile
	
	def login(self):
		""" Automatically login to Bing account """
		self.driver.get(self.login_url)
		
		'''Wait for login button to load before entering email'''
		wait = WebDriverWait(self.driver, self.explicit_wait)
		wait.until(EC.presence_of_all_elements_located((By.ID, 'idSIButton9')))
		
		email_input = self.driver.find_element_by_name('loginfmt')
		email_input.send_keys(self.email)
		
		self.driver.find_element_by_id('idSIButton9').click()
		
		'''Wait for 'Keep me signed in' button to load to enter password'''
		wait = WebDriverWait(self.driver, self.explicit_wait)
		wait.until(EC.presence_of_all_elements_located((By.ID, 'idChkBx_PWD_KMSI0Pwd')))
		
		password_input = self.driver.find_element_by_name('passwd')
		password_input.send_keys(self.password)
		
		self.driver.find_element_by_id('idSIButton9').click()
		
	def get_rand_search_time(self):
		'''Randomize time between searches'''
		return random.uniform(self.min_search_wait, self.max_search_wait)
		
	def get_rand_search_term(self):
		''' Randomly select search term from word list '''
		total_bytes = os.stat(self.word_list).st_size
		random_point = random.randint(0,total_bytes)
		file = open(self.word_list)
		file.seek(random_point)
		term = file.readline()
		file.close()
		return term
		
	def search_bing(self):
		''' Navigate to Bing automatically, search randomly '''
		self.driver.get(self.bing_url)
		
		for search in range(self.num_searches_to_perform):
			''' Wait for search bar to load before querying '''
			wait = WebDriverWait(self.driver, self.explicit_wait)
			wait.until(EC.presence_of_all_elements_located((By.ID, 'sb_form_q')))
		
			rand_word = self.get_rand_search_term()
			self.driver.get('https://bing.com/search?q='+rand_word)
		
			''' Time to wait between searches '''
			rand_time = self.get_rand_search_time()
			time.sleep(rand_time)
			
	def quit(self):
		''' Closes the browser '''
		self.driver.close()
		
	def run(self):
		''' Execute login, search, and quit methods '''
		self.login()
		self.search_bing()
		self.quit()


def main():	
	with open('bing_account.csv', 'r') as f:
		reader = csv.reader(f)
		for row in reader:
			user_id = row[0]
			password = row[1]
		
			bing_bot = BingBot(user_id, password)
			bing_bot.run()
		
			mobile_bing_bot = BingBot(user_id, password, is_mobile=True)
			mobile_bing_bot.run()
			
if __name__ == '__main__':
	main()