# works with both python 2 and 3
from __future__ import print_function
import time
import africastalking

class SMS:
    def __init__(self):
        africastalking.initialize("sandbox", "put-your-key-here")

        # Get the SMS service
        self.sms = africastalking.SMS

    def send(self):
            # Set the numbers you want to send to in international format
            recipients = ["+255755100123", "+255755100124"]

            # Set your message
            message = "Motion Has been detected in your house at " + time.strftime("%I:%M %p on %B %d, %Y")

            # Set your shortCode or senderId
            sender = "55854"
            try:
				# Thats it, hit send and we'll take care of the rest.
                response = self.sms.send(message, recipients, sender)
                print (response)
            except Exception as e:
                print ('Encountered an error while sending: %s' % str(e))


    def fetch_last_sms(self):
        try:
            # Fetch messages with lastReceivedId = 0 to get the most recent messages
            MessageData = self.sms.fetch_messages(1)
            messages = MessageData['SMSMessageData']['Messages']
            
            if len(messages) == 0:
                print('No sms messages in your inbox.')
                return None
            
            # Return just the first message (most recent)
            print("Length of messages: %s" % len(messages))
            return messages[len(messages) - 1]
            
        except Exception as e:
            print('Encountered an error while fetching: %s' % str(e))
            return None


#if __name__ == '__main__':
#    SMS().send()